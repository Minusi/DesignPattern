#include "RValueRefExecutor.h"

#include <iostream>
#include <string>
#include <memory>
#include <algorithm>
#include <utility>
#include <vector>


/*	일반 함수는 R-Value 인자는 R-Value만, L-Value 인자는 L-Value만 받을 수 있지만
 *	템플릿 함수의 R-Value 인자는 R-Value, L-Value 모두를 인자로 받을 수 있다.
 *	
 *	이 예제는 템플릿 기반의 함수가 R-Value Reference의 개념 없이
 *  R-Value가 어떻게 처리될 수 있는 지를 확인하기 위한 실습입니다.
 */
class Dummy
{
public:

	// 이 팩토리 함수는 R-Value에 대해서 호출될 수 없다.
	// ex ) ReturnValue(), 41 등등
	template<typename Arg, typename T>
	std::shared_ptr<T> Factory(Arg& arg)
	{
		return std::shared_ptr<T>(new T{ arg });
	}

	// 이 팩토리 함수는 L-Value를 오버로딩하여 위 함수의 문제점
	// 인 R-Value 호출을 가능하게 하였다.
	// 하지만 이럴 필요의 인자의 갯수가 n개일 때
	// 오버로딩해야할 함수의 갯수는 2^n에 수렴한다.
	template<typename Arg, typename T>
	std::shared_ptr<T> Factory(const Arg& arg)
	{
		return std::shared_ptr<T>(new T{ arg });
	}

	// R-Value Reference 하나로 L-Value와 R-Value를 모두 받을 수 있는 이유는
	// R-Value를 인자로 사용하는 템플릿 함수가 독특한 인자 추론 방법을 사용하기
	// 때문이다:
	// 1. 인자 A타입이 L-Value이면 타입 T는 L-Value Ref, 즉 A&로 추론된다.
	// 2. 인자 A타입이 R-Value이면 타입 T는 R-Value Ref, 즉 A로 추론된다.
	// 여기에 Reference Collapsing Rule(레퍼런스 합침 규칙)이 더해진다.
	// C++11 이전의 C++에서는 레퍼런스의 레퍼런스를 취하는 것이 허용되지 않아
	// A& & 같은 것을 쓰면 컴파일 에러를 발생시켰지만 C++!1은 그렇지 않다.
	// A& & becomes A&
	// A& && becomes A&
	// A&& & becomes A&
	// A&& becomes A&&
	// 따라서,
	// 1. 인자 A 타입이 L-Value이면 타입 T는 A& 추론되므로 A& && = A&가 된다.
	// 2. 인자 A 타입이 R-Value이면 타입 T는 A 추론되므로 A &&가 된다.
	// 하지만 A타입이 L-Value이든 R-Value이든간에 생성자에 전달하는 인자 자체는
	// L-Value이므로 생성자에 L-Value로 전달되는 문제가 있다.
	// # NOTES : R-value 레퍼런스로 정의된 것을은 L-Value일 수도 있고, R-Value
	// 일 수도 있는데, 이름이 있는 경우에는 L-Value, 이름이 없는 경우에는 R-Value
	template<typename Arg, typename T>
	std::shared_ptr<T> RValueFactory(Arg&& arg)
	{
		return std::shared_ptr<T>(new T{ arg });
	}

	// R-Value로 전달하기 위해 std::move를 쓰는 함수이다. 이렇게 사용하게 되면
	// L-Value로 전달되는 것도 R-Value로 캐스팅되므로 값의 손실이 일어나는 위험
	// 한 일이 발생하게 된다.
	template<typename Arg, typename T>
	std::shared_ptr<T> MoveFactory(Arg&& arg)
	{
		return std::shared_ptr<T>(new T{ std::move(arg) });
	}

	// 따라서 이걸 해결하기 위해 std::forward이다.
	// std::forward는 타입을 받아서 &&로 캐스팅 한다. 고로
	// 1. L-Value이면 & &&로 캐스팅 되므로 다음 함수에 &로 포워딩된다.
	// 2. R-Value이면 && &&로 캐스팅 되므로 다음 함수에 &&로 포워딩된다.
	template<typedef Arg, typename T>
	std::shared_ptr<T> PerfectFactory(Arg&& arg)
	{
		return std::shared_ptr<T>(new T{ std::forward(arg) });
	}
};

void RValueTemplateEX1()
{

	class Test
	{
		int i;
	public:
		Test(int InInt) : i(InInt)
		{
			std::cout << InInt << "\tINTConstructor" << std::endl;
		}
		Test(double InDouble) : i(static_cast<int>(InDouble))
		{
			std::cout << InDouble << "\tDOUBLEConstructor" << std::endl;
		}
		Test(float InFloat) : i(static_cast<int>(InFloat))
		{
			std::cout << InFloat << "\tFLOATConstructor" << std::endl;
		}
	};

	Dummy dummy;

	int i = 0;

	// 문제없음. l-value를 Factory함수에 집어넣으므로
	std::shared_ptr<Test>{ dummy.Factory<int, Test>(i) };

	// 문제있음. r-value를 Factory함수에 집어넣으므로
	// 추가로, 다음과 같은 타입으로 형변환 역시 에러를 발생한다:
	// (int)  (int&)  (const int&)0
	// 아래 코드가 작동하면 const Arg&를 오버로딩해야 한다.
	std::shared_ptr<Test>{ dummy.Factory<int, Test>(3)};
}

/* R-Value Reference 예제 1 :
 * 이동 시멘틱을 지원하지 않는 클래스를 구성하고,
 * 벡터의 push_back에 따른 확장에서 불필요한 복사 / 생성이
 * 발생하는지 확인하는 것을 목적으로 합니다.
 */
void RValueMoveSemanticsEX1()
{
	// R-Value 레퍼런스를 구현하지 않은 클래스에 대한 멤버셋입니다.
	class NMemoryBlock
	{
	private:
		size_t Length;
		int* Data;
	public:
		// 생성자
		NMemoryBlock(size_t InLength) : Length(InLength), Data(new int[InLength])
		{
			std::cout << "Constructor Legnth : " << Length << std::endl;
			std::cout << "  Class Location : " << this << std::endl;
		}

		// 소멸자
		~NMemoryBlock()
		{
			std::cout << "Destructor Length : " << Length << std::endl;
			std::cout << "  Class Location : " << this << std::endl;
			delete[] Data;
		}

		// 복사 생성자
		NMemoryBlock(const NMemoryBlock& Other) : Length(Other.Length), Data(new int[Other.Length])
		{
			std::cout << "Copy Constructor Length : " << Length << std::endl;
			std::cout << "  Class Location : " << this << std::endl;
			memcpy_s(Data, Length, Other.Data, Length);
		}

		// 복사 대입 연산자
		NMemoryBlock& operator=(const NMemoryBlock& Other)
		{
			std::cout << "Copy Assignment Operator Length : " << Other.Length << std::endl;

			if (this != &Other)
			{
				delete[] Data;
				
				Length = Other.Length;
				Data = new int[Length];

				memcpy_s(Data, Length, Other.Data, Length);
			}

			return *this;
		}

		// 데이터 리소스의 길이를 반환합니다.
		size_t GetLength() const
		{
			return Length;
		}
	};

	/*	아래 실행 루틴에서 주목할 점은 vector 자체가
	 *	R-Value Reference를 통해서 이동 시멘틱을 지원한다고 해서
	 *	NMemoryBlock 클래스가 이동 시멘틱을 지원하지 않으면
	 *	L-Value Reference로 작동함으로써 성능상의 아무런 이득을
	 *	취할 수 없다는 것이다.
	 *
	 *	아래에 std::move()를 덧씌우는 것은 아무런 의미가 없다.
	 */
	std::vector<NMemoryBlock> vTemp;
	std::cout << "===========================" << std::endl;
	vTemp.push_back(std::move(NMemoryBlock(50)));
	std::cout << "===========================" << std::endl << std::endl;
	vTemp.push_back(std::move(NMemoryBlock(100)));
	std::cout << "===========================" << std::endl << std::endl;
	vTemp[0] = std::move(NMemoryBlock(75));
	std::cout << "===========================" << std::endl << std::endl;
}

/*	R-Value Reference 예제 2 :
 *	이동 시멘틱을 지원하는 클래스를 구성한 다음,
 *  벡터의 push_back에 따른 확장에서 불필요한 복사 / 생성이
 *	발생하는지 확인하는 예제입니다.
 */
void RVlaueMoveSemanticsEX2()
{
	// R-Value 레퍼런스를 구현하지 않은 클래스에 대한 멤버셋입니다.
	class NMemoryBlock
	{
	private:
		size_t Length;
		int* Data;
	public:
		// 생성자
		NMemoryBlock(size_t InLength) : Length(InLength), Data(new int[InLength])
		{
			std::cout << "Constructor Legnth : " << Length << std::endl;
			std::cout << "  Class Location : " << this << std::endl;
		}

		// 소멸자
		~NMemoryBlock()
		{
			std::cout << "Destructor Length : " << Length << std::endl;
			std::cout << "  Class Location : " << this << std::endl;
			delete[] Data;
		}

		// 복사 생성자
		NMemoryBlock(const NMemoryBlock& Other) : Length(Other.Length), Data(new int[Other.Length])
		{
			std::cout << "Copy Constructor Length : " << Length << std::endl;
			std::cout << "  Class Location : " << this << std::endl;
			memcpy_s(Data, Length, Other.Data, Length);
		}

		// 이동 생성자
		NMemoryBlock(NMemoryBlock&& Other) : Data(nullptr), Length(0)
		{
			std::cout << "Move Constructor Length : " << Other.Length << std::endl;
			*this = std::move(Other);
		}

		// 복사 대입 연산자
		NMemoryBlock& operator=(const NMemoryBlock& Other)
		{
			std::cout << "Copy Assignment Operator Length : " << Other.Length << std::endl;

			if (this != &Other)
			{
				delete[] Data;

				Length = Other.Length;
				Data = new int[Length];

				memcpy_s(Data, Length, Other.Data, Length);
			}

			return *this;
		}

		// 이동 대입 연산자
		NMemoryBlock& operator=(NMemoryBlock&& Other)
		{
			std::cout << "Move Assignment Operator Lengh " << Other.Length << std::endl;

			if (this !=  &Other)
			{
				delete[] Data;

				Data = Other.Data;
				Length = Other.Length;

				Other.Data = nullptr;
				Other.Length = 0;
			}

			return *this;
		}

		// 데이터 리소스의 길이를 반환합니다.
		size_t GetLength() const
		{
			return Length;
		}
	};

	std::vector<NMemoryBlock> vTemp;
	std::cout << "================================" << std::endl;
	vTemp.push_back(NMemoryBlock(50));
	std::cout << "================================" << std::endl;
	vTemp.push_back(NMemoryBlock(100));
	std::cout << "================================" << std::endl;
	vTemp[0] = NMemoryBlock(75);
	std::cout << "================================" << std::endl<< std::endl;

	std::cout << "================================" << std::endl;
	std::vector<NMemoryBlock> vTemp2;
	std::cout << "================================" << std::endl;
	vTemp2.push_back(NMemoryBlock(50));
	std::cout << "================================" << std::endl;
	vTemp2.push_back(NMemoryBlock(100));
	std::cout << "================================" << std::endl;
	vTemp2[0] = NMemoryBlock(75);
	std::cout << "================================" << std::endl;

}



/*	이 예제는 std::move의 잘못된 사용에 대한 위험을 알아보는 예제이다.
 *	예제에서 주어진 Dummy1의 SetString은 Universal ref로 추정되는 InString을
 *	인자로 받아 이동 시멘틱을 수행하는 클래스이다.
 *	STDMoveCautionEX1 내에서 L-Value인자를 SetString에 대입했을 떄
 *	L-Value의 값의 손실이 일어나게 되고 콘솔에서는 빈 문자열을 출력한다.
 *	
 */
class Dummy1
{
private:
	std::string dummystring;

public:
	Dummy1() : dummystring()
	{

	}

	Dummy1(std::string InString) : dummystring(InString)
	{

	}

	//void SetString(std::string& InString)
	//{
	//	std::cout << "ENTER::U-Value SetString" << std::endl;
	//	dummystring = InString;
	//}

	template<typename T>
	void SetString(T&& InString)
	{
		std::cout << "ENTER::R-Value SetString" << std::endl;
		dummystring = std::move(InString);
	}
};

void STDMoveCautionEX1()
{
	Dummy1 d;
	std::string hello = "Hello";
	
	d.SetString(hello);

	std::cout << "\"" << hello << "\"" << std::endl;
}

/*	인자를 rvalue reference로 받았고 리턴은 value타입으로 해야되는 경우,
 *	우리는 리턴값을 따로 만들어서 반환해야 한다. 이 떄 std::move 또는 
 *	std::forward를 사용하는 것이 이득이다.( forward는 universal ref인자일때 )
 *	아래의 ReturnValueWithMoveEX1()은 작동되지는 않지만 예제 자료로써 
 *	들고 왔다.
 *	CASE1의 경우 return을 위한 복사생성자가 호출될 것이나
 *	CASE2의 경우 return을 위한 이동생성자가 호출될 것이다.
 */
void ReturnValueWithMoveEX1()
{
	class Matrix
	{
	private: 
		int value;
	public:
		Matrix operator+(Matrix&& rhs)
		{
			rhs.value += this->value;
#ifdef CASE1
			return rhs;
#elif CASE2
			return std::move(rhs);
#endif
			return rhs;
		}
	};
}

/*	무조건 r-value reference라고 move를 이용한 반환은 오히려 성능상의 손실을 부른다.
 *	바로 컴파일러 최적화 중 하나인 RVO(return vlaue optimization)으로, RVO 최적화는
 *	저장공간에 복사를 해서 반환하는 것이 아니라 지역변수의 주소를 그대로 전달하는 최적
 *	화 기법이다.
 *
 *	RVO에는 다음과 같은 조건이 있다. 우선 지역 변수 타입이 반환 타입과 일치할 것.
 *	그리고 반환값이 지역 변수일 것. 이것을 충족시키면 RVO가 수행된다. 
 *	아래 예제는 RVO 조건을 만족시키는 지역변수에 대한 케이스이다.
 *	CASE1에서는 RVO를 만족하나 CASE2에서는 std::move에 의해 함수 내의 지역변수라는 조건에
 *	위배된다. 따라서 move 생성자를 호출하여 반환값을 생성한다.
 *
 *	RVO조건이 맞아도 컴파일러가 적합한 저장소를 찾기 힘든 경우가 발생할 수 있다. 그렇게 되면
 *	결국 copy / move 연산을 피할 수 없을 거라는 예상과는 달리 이 경우 컴파일러는
 *	모든 가능한 return 지역변수들을 r-value reference로 캐스팅하여 반환한다.
 */
void DoNotMoveWithRVOEX1()
{
	class Widget
	{
	public:
		Widget makeWidget()
		{
			Widget w;
#ifdef _CASE1
			return w;				// RVO 최적화의 대상
									// 실패시 이 코드를 return std::move(w);로 변환
#elif _CASE2
			return std::move(w);	// RVO 최적화보다 느린 이동 시멘틱 수행
#endif
		}
	};
}

void RValueRefExecutor::ExecutePattern()
{
	//RValueTemplateEX1();

	//RValueMoveSemanticsEX1();
	//RVlaueMoveSemanticsEX2();

	STDMoveCautionEX1();
}
