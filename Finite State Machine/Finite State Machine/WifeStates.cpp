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

		std::cout << GetNameOfEntity(pWife->ID()) << ": ���. �� �����ٰ�" << std::endl;

		pWife->GetFSM()->ChangeState(CookMeal::Instance());

		return true;
	}
	case Msg_GoToWork:
	{
		std::cout << "Message handled by " << GetNameOfEntity(pWife->ID()) << " at time: " << Clock->GetCurrentTime() << std::endl;

		SetTextColor(FOREGROUND_GREEN | FOREGROUND_INTENSITY);

		std::cout << GetNameOfEntity(pWife->ID()) << ": �� �ٳ��. ���������ϰ�.~" << std::endl;

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
		std::cout << GetNameOfEntity(pWife->ID()) << ": ���� ���� ���� �� ����?" << std::endl;

		pWife->ChangeLocation(Home);
	}
}

void DoHouseWork::Execute(Wife* pWife)
{
	enum
	{
		û��, ��Ź, ������
	};

	std::uniform_int_distribution<> uid(0, 2);
	std::cout << GetNameOfEntity(pWife->ID());

	switch (uid(dre))
	{
	case û��:
		std::cout << ": û�� ��" << std::endl;
		break;
	case ��Ź:
		std::cout << ": ���� ��" << std::endl;
		break;
	case ������:
		std::cout << ": ������ ��" << std::endl;
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
	std::cout << GetNameOfEntity(pWife->ID()) << ": �庸�� ����?" << std::endl;
}

void ShopAtTheMarket::Execute(Wife* pWife)
{
	std::cout << GetNameOfEntity(pWife->ID()) << ": ������ ���� ǰ���� �����? ��, ��ī��!~" << std::endl;

	pWife->GetFSM()->RevertToPreviousState();
}

void ShopAtTheMarket::Exit(Wife* pWife)
{
	std::cout << GetNameOfEntity(pWife->ID()) << ": Ư�� ������ ���� �ְ��!" << std::endl;
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
			std::cout << ": ������ ���뱹���� �غ���?" << std::endl;
			break;
		case 1:
			std::cout << ": ������ �ᳪ�������� �غ���?" << std::endl;
			break;
		case 2:
			std::cout << ": ������ ���������� �غ���?" << std::endl;
			break;
		}

		Dispatch->DispatchMessage(1.5, pWife->ID(), pWife->ID(), Msg_CookingFinished, reinterpret_cast<void*>(NO_ADDITIONAL_INFO));

		pWife->StartCooking(true);
	}
}

void CookMeal::Execute(Wife* pWife)
{
	std::cout << GetNameOfEntity(pWife->ID()) << ": ���� ��" << std::endl;
}

void CookMeal::Exit(Wife* pWife)
{
	SetTextColor(FOREGROUND_GREEN | FOREGROUND_INTENSITY);

	std::cout << GetNameOfEntity(pWife->ID()) << ": �Ļ� �غ� �������ϱ� �ͼ� �� �Ծ�." << std::endl;
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
		
		std::cout << GetNameOfEntity(pWife->ID()) << ": ���ְ� �� ���.�׷� ���� �׸��� ���..." << std::endl;

		pWife->StartCooking(false);
		pWife->GetFSM()->ChangeState(DoHouseWork::Instance());

		Dispatch->DispatchMessage(SEND_MSG_IMMEDIATELY, pWife->ID(), ent_Jeff, Msg_CookingFinished, reinterpret_cast<void*>(NO_ADDITIONAL_INFO));
		Dispatch->DispatchMessage(SEND_MSG_IMMEDIATELY, pWife->ID(), ent_Eris, Msg_CookingFinished, reinterpret_cast<void*>(NO_ADDITIONAL_INFO));
	}
	return true;
	}

	return false;
}