#include "SmartPointerExecutor.h"



/*
 *	C 스타일의 스마트 포인터 예제들에 대한 함수들 모음
 */

void SmartPointerEX1()
{
	std::unique_ptr<int> Up1 = std::unique_ptr<int>(new int{ 10 });

	std::cout << *Up1 << std::endl;
}

void SmartPointerEX2()
{

	std::unique_ptr<int> Up1 = std::unique_ptr<int>{ new int{10} };
	std::cout << *Up1 << std::endl;


	std::unique_ptr<int> Up2 = std::move(Up1);
}


void WeakPointerEX1()
{
	// Strong RefCount = 1
	std::shared_ptr<int> sp1 = std::shared_ptr<int>{ new int{5} };

	std::weak_ptr<int> wp1 = sp1;
	{
		// Lock 함수를 통해서 
		std::shared_ptr<int> sp2 = wp1.lock();
		if (sp2)
		{
			std::cout << "sp2 is not null" << std::endl;
		}
		else
		{
			std::cout << "sp2 is null" << std::endl;
		}
	}

	sp1.reset();

	std::shared_ptr<int> sp3 = wp1.lock();
	if (sp3 != nullptr)
	{
		std::cout << "sp3 is not null" << std::endl;
	}
	else
	{
		std::cout << "sp3 is null" << std::endl;
	}
}

#include <vector>

void WeakPointerEX2()
{

	class User;
	typedef std::shared_ptr<User> UserPtr;

	class Party
	{
	public:
		Party()
		{
			std::cout << "Party is created" << std::endl;
		}
		virtual ~Party()
		{
			std::cout << "Party is disassembled" << std::endl;
			m_MemberList.clear();
		}

	public:
		void AddMember(const UserPtr& Member)
		{
			m_MemberList.push_back(Member);
		}

		void RemoveMember()
		{
			m_MemberList.clear();
		}

	private:
		typedef std::vector<UserPtr> MemberList;
		MemberList m_MemberList;
	};



	typedef std::shared_ptr<Party> PartyPtr;
	typedef std::weak_ptr<Party> PartyWeakPtr;

	class User
	{
	public:
		User(std::string UserName) : m_UserName(UserName)
		{
			std::cout << m_UserName << " enter the game" << std::endl;
		}

		~User()
		{
			std::cout << m_UserName << " leave the party" << std::endl;
		}

	public:
		void SetParty(const PartyPtr& Party)
		{
			m_Party = Party;
		}


		void LeaveParty()
		{
			if (!m_Party.expired())
			{
				PartyPtr partyPtr = m_Party.lock();
				if (partyPtr)
				{
					partyPtr->RemoveMember();
				}
			}
		}

	private:
		PartyWeakPtr m_Party;
		std::string m_UserName;
	};

	// party의 strong refcoune = 1;
	PartyPtr party(new Party);

	for (int i = 0; i < 5; ++i)
	{
		// user의 strong refCount = 1;
		UserPtr user(new User(std::to_string(i) + " User"));

		// user의 strong refCount = 2;
		party->AddMember(user);

		// 약포인터 참조이므로 party의 strong refcoune = 1;
		user->SetParty(party);

	}	// 스코프로 인해 user의 refCount = 1;

	party.reset();
}


void NSmartPointerExecutor::ExecutePattern()
{
	//SmartPointerEX1();

	//WeakPointerEX1();

	WeakPointerEX2();
}

