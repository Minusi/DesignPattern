#include "RawPointerExecutor.h"

#include <iostream>
#include <string>
#include <memory>
#include <cstdlib>



/*
 *	Raw Pointer 연습 함수들 시작 지점
 */

// 함수 내 지역 객체를 참조 형식으로 반환했을 때의
// 스코프 변경으로 인한 문제점
void RawPointerEX1()
{
	class Nested
	{
	public:
		int& function()
		{
			int val = 10;
			return val;
		}

		int& function2()
		{
			int val = 20;
			return val;
		}

		int* pfunction()
		{
			int val = 10;
			return &val;
		}

		int* pfunction2()
		{
			int val = 20;
			return &val;
		}
	};

	Nested nested;
	
	int& ref = nested.function();
	std::cout << std::endl;
	// 왜인지는 모르겠지만 45라인에서 값을 넘겨받고나면
	// 46라인이 실행된 후에야 메모리 값에 null이 발생한다.
	// 아래 모든 ref2, pref, pref2에도 해당되는 얘기이다.
	std::cout << ref << std::endl;

	int& ref2 = nested.function2();
	std::cout << std::endl;
	std::cout << ref2 << std::endl;
	std::cout << ref << std::endl;


	int* pref = nested.pfunction();
	std::cout << std::endl;
	std::cout << *pref << std::endl;

	int* pref2 = nested.pfunction2();
	std::cout << std::endl;
	std::cout << *pref2 << std::endl;
	std::cout << *pref << std::endl;

	std::cout << std::endl << std::endl;

	std::cout << ref << std::endl << ref2 << std::endl;
	std::cout << *pref << std::endl << *pref2 << std::endl;
}

// 참조자에 의한 전달이 효율적이라고 해서 항상 참조자를 반환하려 들면 안됩니다.
// 참조라를 리턴하려는 경우 바생하는 문제는 다음과 같습니다.
//
// 함수 내 지역객체의 참조자를 반환
// : 쓰레기값을 가진 참조자가 반환됩니다.
// 힙 기반의 객체를 참조자로 반환
// : 어차피 생성자가 호출되는 것은 똑같습니다.
// : 함수 내 힙 기반 객체를 delete할 방법이 없습니다.
// 아래의 예제는 2개의 객체가 메모리 누수를 일으키는 문제를 야기합니다.
void RawPointerEX2()
{
	static int cid = 0;

	class Dummy
	{
	private:
		int n, d;
		std::string s;

	public:
		Dummy(int InN, int InD, std::string InS) : n(InN) , d(InD), s(InS)
		{
			std::cout << "  Create::Dummy(" << s << ")\t" << ++cid << std::endl;
			std::cout << this << std::endl << std::endl;
		}
		~Dummy()
		{
			std::cout << "  Delete::Dummy(" << s << ")\t" << --cid << std::endl;
			std::cout << this << std::endl << std::endl;
		}
		Dummy(const Dummy& rhs)
		{
			std::cout << "  Copier::Dummy(" << rhs.s << ")\t" << ++cid << std::endl;
			std::cout << this << std::endl << std::endl;

			this->n = rhs.n;
			this->d = rhs.d;
			this->s = rhs.s;
		}

		Dummy& operator=(const Dummy& rhs)
		{
			std::cout << "  Insert::Dummy(" << rhs.s << ")\t" << cid << std::endl;
			std::cout << this << std::endl << std::endl;

			this->n = rhs.n;
			this->d = rhs.d;
			this->s = rhs.s;

			return *this;
		}

		Dummy& operator+(const Dummy& rhs)
		{
			std::cout << "  Enter::Operator+" << std::endl;
			// 내 생각으로는 이 문제는 복사 연산자에서 delete 하지 않는 것의 문제일 뿐이라고
			// 생각함.
			Dummy* dummy = new Dummy(this->n + rhs.n, this->d + rhs.d, this->s + rhs.s);

			return *dummy;
		}
	};

	Dummy w(1,1,"w"), x(2,2, "x"), y(3,3, "y"), z(4,4, "z");
	
	//Dummy(w)와 Dummy(xy)가 delete 되지 않는다.
	w = x + y + z;
}

void RawPointerToSmartEX2()
{
	static int cid = 0;
	class Dummy
	{
	private:
		int n, d;
		std::string s;

	public:
		Dummy(int InN, int InD, std::string InS) : n(InN), d(InD), s(InS)
		{
			std::cout << "  Create::Dummy(" << s << ")\t" << ++cid << std::endl;
			std::cout << "  " << this << std::endl;
		}
		~Dummy()
		{
			std::cout << "  Delete::Dummy(" << s << ")\t" << --cid << std::endl;
			std::cout << "  " << this << std::endl;
		}
		Dummy(const Dummy& rhs)
		{
			std::cout << "  Copier::Dummy(" << rhs.s << ")\t" << ++cid << std::endl;
			std::cout << "  " << this << std::endl;

			this->n = rhs.n;
			this->d = rhs.d;
			this->s = rhs.s;
		}


		Dummy operator+(const Dummy& rhs)
		{
			std::cout << std::endl << "  Enter::Operator+\t" << this->s << std::endl;
			Dummy dummy{ Dummy(this->n + rhs.n, this->d + rhs.d, this->s + rhs.s) };

			std::cout << "  Exit::Operator+" << std::endl;
			return dummy;
		}
		
	};

	/*	전체적인 워크플로우 ;
	 *	x 생성자
	 *	y 생성자
	 *	z 생성자
	 *	+ 연산자 내 스택 생성자
	 *	+ 연산자 내 반환 복사생성자
	 *	+ 연산자 내 스택 소멸자
	 *	반환 소멸자
	 *	z 소멸자
	 *	y 소멸자
	 *	x 소멸자
	*/

	Dummy* pdum;

	//Dummy w(1, 1, "w");
	Dummy x(2, 2, "x");
	Dummy y(3, 3, "y");
	Dummy z(4, 4, "z");


	Dummy w = x+y;// +z;
	std::cout << std::endl;
	pdum = &w;
	std::cout << std::endl << "  " << pdum << std::endl << std::endl;
}

void RawPointerEX3()
{
	class Dummy
	{
	public:
		//int& GetInt()
		//{
		//	int i;
		//	return i;
		//}
		
		int& GetInt()
		{
			int* i = new int{ 5 };
			return *i;
		}
	};

	Dummy dummy;
	
	int& myint = dummy.GetInt();
	int badint = dummy.GetInt();
	
	std::cout << myint << std::endl;
	delete &myint;

	// 동적 할당된 i를 delete 할 수 없다.
	std::cout << badint << std::endl;
	//error occur ~~v
	//delete &badint;
	
}



/*
 *	Raw Pointer Main 함수 진입 지점
 */

void NRawPointerExecutor::ExecutePattern()
{
	//RawPointerEX1();

	RawPointerEX2();
	//RawPointerToSmartEX2();

	//RawPointerEX3();

 }