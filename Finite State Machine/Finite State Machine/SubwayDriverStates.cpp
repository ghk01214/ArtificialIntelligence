#include "SubwayDriverStates.h"
#include "../../Common/fsm/State.h"
#include "SubwayDriver.h"
#include "Locations.h"
#include "../../Common/messaging/Telegram.h"
#include "MessageDispatcher.h"
#include "MessageTypes.h"
#include "../../Common/Time/CrudeTimer.h"
#include "EntityNames.h"

#include <iostream>

#ifdef TEXTOUTPUT
#include <fstream>
extern std::ofstream os;
#define std::cout os
#endif

GoOutForDriving* GoOutForDriving::Instance()
{
	static GoOutForDriving instance;

	return &instance;
}

void GoOutForDriving::Enter(SubwayDriver* pSubwayDriver)
{
	SetTextColor(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY);

	if (pSubwayDriver->Location() != Subway)
	{
		std::cout << GetNameOfEntity(pSubwayDriver->ID()) << ": " << "���� �غ� ��" << std::endl;

		pSubwayDriver->ChangeLocation(Subway);
	}
}

void GoOutForDriving::Execute(SubwayDriver* pSubwayDriver)
{
	pSubwayDriver->AddDriveTimes();
	pSubwayDriver->IncreaseFatigue();

	std::cout << GetNameOfEntity(pSubwayDriver->ID()) << ": " << "����ö ���� ��" << std::endl;

	if (pSubwayDriver->DangerForDriving())
		pSubwayDriver->GetFSM()->ChangeState(RestForNextDrive::Instance());
	else
	{
		pSubwayDriver->AddDriveTimes();
		pSubwayDriver->IncreaseHunger();
	}

	if (pSubwayDriver->Hunger())
	{
		if (!pSubwayDriver->AteLunch())
			pSubwayDriver->GetFSM()->ChangeState(EatLunchAtCafeteria::Instance());
		else
		{
			for (int i = 0; i < 7; ++i)
				pSubwayDriver->IncreaseFatigue();
			
			pSubwayDriver->GetFSM()->ChangeState(GoHomeAndSleepTilRested::Instance());
		}
	}
}

void GoOutForDriving::Exit(SubwayDriver* pSubwayDriver)
{
	std::cout << GetNameOfEntity(pSubwayDriver->ID()) << ": " << "�̹� ���൵ ����� �����̾���." << std::endl;
}

bool GoOutForDriving::OnMessage(SubwayDriver* pSubwayDriver, const Telegram& msg)
{
	return false;
}

//=========================================================================================================================================

RestForNextDrive* RestForNextDrive::Instance()
{
	static RestForNextDrive instance;

	return &instance;
}

void RestForNextDrive::Enter(SubwayDriver* pSubwayDriver)
{
	if (pSubwayDriver->Location() != Company)
	{
		std::cout << GetNameOfEntity(pSubwayDriver->ID()) << ": " << "����� �ްԽ� ����" << std::endl;

		pSubwayDriver->ChangeLocation(Company);
	}
}

void RestForNextDrive::Execute(SubwayDriver* pSubwayDriver)
{
	pSubwayDriver->AddDriveTimes();
	pSubwayDriver->DecreaseFatigue();

	std::cout << GetNameOfEntity(pSubwayDriver->ID()) << ": " << "�޽� ��" << std::endl;

	if (pSubwayDriver->GetFatigue() <= 0)
		pSubwayDriver->GetFSM()->ChangeState(GoOutForDriving::Instance());
	else
		pSubwayDriver->DecreaseFatigue();

	if (pSubwayDriver->Hunger())
		pSubwayDriver->GetFSM()->ChangeState(EatLunchAtCafeteria::Instance());
}

void RestForNextDrive::Exit(SubwayDriver* pSubwayDriver)
{
	std::cout << GetNameOfEntity(pSubwayDriver->ID()) << ": " << "����� �������� �ٽ� ������ ��������?" << std::endl;
}

bool RestForNextDrive::OnMessage(SubwayDriver* pSubwayDriver, const Telegram& msg)
{
	return false;
}

//=========================================================================================================================================

GoHomeAndSleepTilRested* GoHomeAndSleepTilRested::Instance()
{
	static GoHomeAndSleepTilRested instance;

	return &instance;
}

void GoHomeAndSleepTilRested::Enter(SubwayDriver* pSubwayDriver)
{
	if (pSubwayDriver->Location() != Home)
	{
		pSubwayDriver->EatLunch(false);

		std::cout << GetNameOfEntity(pSubwayDriver->ID()) << ": " << "�ٳ�Ծ�." << std::endl;

		pSubwayDriver->ChangeLocation(Home);
		Dispatch->DispatchMessage(SEND_MSG_IMMEDIATELY, pSubwayDriver->ID(), ent_Sam, Msg_HiImHome, reinterpret_cast<void*>(NO_ADDITIONAL_INFO));
		Dispatch->DispatchMessage(SEND_MSG_IMMEDIATELY, pSubwayDriver->ID(), ent_Eris, Msg_HiImHome, reinterpret_cast<void*>(NO_ADDITIONAL_INFO));
	}
}

void GoHomeAndSleepTilRested::Execute(SubwayDriver* pSubwayDriver)
{
	if (!pSubwayDriver->Fatigued())
	{
		std::cout << GetNameOfEntity(pSubwayDriver->ID()) << ": " << "����~. �� ���. ���õ� ���ο� �Ϸ縦 ������ ����?" << std::endl;

		pSubwayDriver->GetFSM()->ChangeState(GoOutForDriving::Instance());
	}
	else
	{
		pSubwayDriver->DecreaseFatigue();

		std::cout << GetNameOfEntity(pSubwayDriver->ID()) << ": " << "ZZZZ... " << std::endl;
	}
}

void GoHomeAndSleepTilRested::Exit(SubwayDriver* pSubwayDriver)
{
	if (!pSubwayDriver->Hunger())
	{
		std::cout << GetNameOfEntity(pSubwayDriver->ID()) << ": " << "�ٳ�ð�." << std::endl;

		Dispatch->DispatchMessage(SEND_MSG_IMMEDIATELY, pSubwayDriver->ID(), ent_Sam, Msg_GoToWork, reinterpret_cast<void*>(NO_ADDITIONAL_INFO));
		Dispatch->DispatchMessage(SEND_MSG_IMMEDIATELY, pSubwayDriver->ID(), ent_Eris, Msg_GoToWork, reinterpret_cast<void*>(NO_ADDITIONAL_INFO));
	}
}

bool GoHomeAndSleepTilRested::OnMessage(SubwayDriver* pSubwayDriver, const Telegram& msg)
{
	SetTextColor(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY);

	switch (msg.Msg)
	{
	case Msg_CookingFinished:

		std::cout << "Message handled by " << GetNameOfEntity(pSubwayDriver->ID()) << " at time: " << Clock->GetCurrentTime() << std::endl;

		SetTextColor(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY);

		std::cout << GetNameOfEntity(pSubwayDriver->ID()) << ": �˾Ҿ�. ���� ����." << std::endl;;

		pSubwayDriver->GetFSM()->ChangeState(EatAndDrinkAtHome::Instance());

		return true;
	}

	return false;
}

//=========================================================================================================================================

EatLunchAtCafeteria* EatLunchAtCafeteria::Instance()
{
	static EatLunchAtCafeteria instance;

	return &instance;
}

void EatLunchAtCafeteria::Enter(SubwayDriver* pSubwayDriver)
{
	if (pSubwayDriver->Location() != Cafeteria)
	{
		pSubwayDriver->ChangeLocation(Cafeteria);

		std::cout << GetNameOfEntity(pSubwayDriver->ID()) << ": " << "������ �� ������?" << std::endl;
	}
}

void EatLunchAtCafeteria::Execute(SubwayDriver* pSubwayDriver)
{
	pSubwayDriver->FillingFull();
	pSubwayDriver->EatLunch(true);

	std::cout << GetNameOfEntity(pSubwayDriver->ID()) << ": " << "�ӳɳ�" << std::endl;

	if (pSubwayDriver->GetFSM()->PreviousState() == RestForNextDrive::Instance())
		pSubwayDriver->GetFSM()->RevertToPreviousState();
	else
		pSubwayDriver->GetFSM()->ChangeState(GoOutForDriving::Instance());
}

void EatLunchAtCafeteria::Exit(SubwayDriver* pSubwayDriver)
{
	std::cout << GetNameOfEntity(pSubwayDriver->ID()) << ": " << "�� ��θ���. ���־���." << std::endl;
}

bool EatLunchAtCafeteria::OnMessage(SubwayDriver* pSubwayDriver, const Telegram& msg)
{
	return false;
}

//=========================================================================================================================================

EatAndDrinkAtHome* EatAndDrinkAtHome::Instance()
{
	static EatAndDrinkAtHome instance;

	return &instance;
}

void EatAndDrinkAtHome::Enter(SubwayDriver* pSubwayDriver)
{
	std::cout << GetNameOfEntity(pSubwayDriver->ID()) << ": " << "���� ���־� ���̳�. �߸԰ڽ��ϴ�." << std::endl;
}

void EatAndDrinkAtHome::Execute(SubwayDriver* pSubwayDriver)
{
	std::cout << GetNameOfEntity(pSubwayDriver->ID()) << ": " << "����.~ ���� �츮 ������ ����� �ִ� ������ �ְ��ϱ�!" << std::endl;

	pSubwayDriver->GetFSM()->RevertToPreviousState();
}

void EatAndDrinkAtHome::Exit(SubwayDriver* pSubwayDriver)
{
	pSubwayDriver->FillingFull();
	std::cout << GetNameOfEntity(pSubwayDriver->ID()) << ": " << "���� �߸Ծ���. ���� �ϴ� ���� ���� �� ����" << std::endl;
}

bool EatAndDrinkAtHome::OnMessage(SubwayDriver* pSubwayDriver, const Telegram& msg)
{
	return false;
}