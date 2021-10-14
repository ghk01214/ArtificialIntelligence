#include "WifeStates.h"
#include "SubwayDriverStates.h"
#include "Wife.h"
#include "Locations.h"
#include "../Common/Time/CrudeTimer.h"
#include "MessageDispatcher.h"
#include "MessageTypes.h"
#include "EntityNames.h"

#include <iostream>
#include <random>

#ifdef TEXTOUTPUT
#include <fstream>
extern std::ofstream os;
#define std::cout os
#endif

std::random_device rd;
std::default_random_engine dre(rd());

WifesGlobalState* WifesGlobalState::Instance()
{
	static WifesGlobalState instance;

	return &instance;
}

void WifesGlobalState::Execute(Wife* pWife)
{
	std::uniform_real_distribution<> urd(0.0, 1.0);

	if (urd(dre) < 0.1 && pWife->Location() != Market  && !pWife->GetFSM()->isInState(*CookMeal::Instance()))
	{
		pWife->ChangeLocation(Market);

		pWife->GetFSM()->ChangeState(ShopAtTheMarket::Instance());
	}
}

bool WifesGlobalState::OnMessage(Wife* pWife, const Telegram& msg)
{
	SetTextColor(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY);

	switch (msg.Msg)
	{
	case Msg_HiImHome:
	{
		std::cout << "Message handled by " << GetNameOfEntity(pWife->ID()) << " at time: " << Clock->GetCurrentTime() << std::endl;

		SetTextColor(FOREGROUND_GREEN | FOREGROUND_INTENSITY);

		std::cout << GetNameOfEntity(pWife->ID()) << ": 어서와. 밥 차려줄게" << std::endl;

		pWife->GetFSM()->ChangeState(CookMeal::Instance());

		return true;
	}
	case Msg_GoToWork:
	{
		std::cout << "Message handled by " << GetNameOfEntity(pWife->ID()) << " at time: " << Clock->GetCurrentTime() << std::endl;

		SetTextColor(FOREGROUND_GREEN | FOREGROUND_INTENSITY);

		std::cout << GetNameOfEntity(pWife->ID()) << ": 잘 다녀와. 안전운행하고.~" << std::endl;

		pWife->GetFSM()->ChangeState(DoHouseWork::Instance());

		return true;
	}
	}

	return false;
}

//=========================================================================================================================================

DoHouseWork* DoHouseWork::Instance()
{
	static DoHouseWork instance;

	return &instance;
}

void DoHouseWork::Enter(Wife* pWife)
{
	if (pWife->Location() != Home)
	{
		std::cout << GetNameOfEntity(pWife->ID()) << ": 쌓인 집안 일을 해 볼까?" << std::endl;

		pWife->ChangeLocation(Home);
	}
}

void DoHouseWork::Execute(Wife* pWife)
{
	enum
	{
		청소, 세탁, 설거지
	};

	std::uniform_int_distribution<> uid(0, 2);
	std::cout << GetNameOfEntity(pWife->ID());

	switch (uid(dre))
	{
	case 청소:
		std::cout << ": 청소 중" << std::endl;
		break;
	case 세탁:
		std::cout << ": 빨래 중" << std::endl;
		break;
	case 설거지:
		std::cout << ": 설거지 중" << std::endl;
		break;
	}
}

void DoHouseWork::Exit(Wife* pWife)
{
}

bool DoHouseWork::OnMessage(Wife* pWife, const Telegram& msg)
{
	return false;
}

//=========================================================================================================================================

ShopAtTheMarket* ShopAtTheMarket::Instance()
{
	static ShopAtTheMarket instance;

	return &instance;
}

void ShopAtTheMarket::Enter(Wife* pWife)
{
	std::cout << GetNameOfEntity(pWife->ID()) << ": 장보러 갈까?" << std::endl;
}

void ShopAtTheMarket::Execute(Wife* pWife)
{
	std::cout << GetNameOfEntity(pWife->ID()) << ": 오늘의 할인 품목은 뭘까요? 피, 피카츄!~" << std::endl;

	pWife->GetFSM()->RevertToPreviousState();
}

void ShopAtTheMarket::Exit(Wife* pWife)
{
	std::cout << GetNameOfEntity(pWife->ID()) << ": 특별 세일은 정말 최고야!" << std::endl;
}

bool ShopAtTheMarket::OnMessage(Wife* pWife, const Telegram& msg)
{
	return false;
}

//=========================================================================================================================================

CookMeal* CookMeal::Instance()
{
	static CookMeal instance;

	return &instance;
}

void CookMeal::Enter(Wife* pWife)
{
	std::uniform_int_distribution<> uid(0, 2);

	if (!pWife->Cooking())
	{
		std::cout << GetNameOfEntity(pWife->ID());

		switch (uid(dre))
		{
		case 0:
			std::cout << ": 오늘은 순대국밥을 해볼까?" << std::endl;
			break;
		case 1:
			std::cout << ": 오늘은 콩나물국밥을 해볼까?" << std::endl;
			break;
		case 2:
			std::cout << ": 오늘은 돼지국밥을 해볼까?" << std::endl;
			break;
		}

		Dispatch->DispatchMessage(1.5, pWife->ID(), pWife->ID(), Msg_CookingFinished, reinterpret_cast<void*>(NO_ADDITIONAL_INFO));

		pWife->StartCooking(true);
	}
}

void CookMeal::Execute(Wife* pWife)
{
	std::cout << GetNameOfEntity(pWife->ID()) << ": 조리 중" << std::endl;
}

void CookMeal::Exit(Wife* pWife)
{
	SetTextColor(FOREGROUND_GREEN | FOREGROUND_INTENSITY);

	std::cout << GetNameOfEntity(pWife->ID()) << ": 식사 준비 끝났으니까 와서 밥 먹어." << std::endl;
}

bool CookMeal::OnMessage(Wife* pWife, const Telegram& msg)
{
	SetTextColor(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY);

	switch (msg.Msg)
	{
	case Msg_CookingFinished:
	{
		std::cout << "Message received by " << GetNameOfEntity(pWife->ID()) << " at time: " << Clock->GetCurrentTime() << std::endl;

		SetTextColor(FOREGROUND_GREEN | FOREGROUND_INTENSITY);
		
		std::cout << GetNameOfEntity(pWife->ID()) << ": 맛있게 잘 됬네.그럼 이제 그릇에 담고..." << std::endl;

		pWife->StartCooking(false);
		pWife->GetFSM()->ChangeState(DoHouseWork::Instance());

		Dispatch->DispatchMessage(SEND_MSG_IMMEDIATELY, pWife->ID(), ent_Jeff, Msg_CookingFinished, reinterpret_cast<void*>(NO_ADDITIONAL_INFO));
		Dispatch->DispatchMessage(SEND_MSG_IMMEDIATELY, pWife->ID(), ent_Eris, Msg_CookingFinished, reinterpret_cast<void*>(NO_ADDITIONAL_INFO));
	}
	return true;
	}

	return false;
}