#include "DaughterStates.h"
#include "SubwayDriverStates.h"
#include "Daughter.h"
#include "Locations.h"
#include "../../Common/Time/CrudeTimer.h"
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

extern std::random_device rd;
extern std::default_random_engine dre;

DaughtersGlobalState* DaughtersGlobalState::Instance()
{
	static DaughtersGlobalState instance;

	return &instance;
}

void DaughtersGlobalState::Execute(Daughter* pDaughter)
{
}

bool DaughtersGlobalState::OnMessage(Daughter* pDaughter, const Telegram& msg)
{
	SetTextColor(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY);

	switch (msg.Msg)
	{
	case Msg_HiImHome:
	{
		std::cout << "Message handled by " << GetNameOfEntity(pDaughter->ID()) << " at time: " << Clock->GetCurrentTime() << std::endl;

		SetTextColor(FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY);

		std::cout << GetNameOfEntity(pDaughter->ID()) << ": �ٳ���̾��." << std::endl;

		return true;
	}
	case Msg_GoToWork:
	{
		std::cout << "Message handled by " << GetNameOfEntity(pDaughter->ID()) << " at time: " << Clock->GetCurrentTime() << std::endl;

		SetTextColor(FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY);

		std::cout << GetNameOfEntity(pDaughter->ID()) << ": �ٳ������." << std::endl;

		pDaughter->GetFSM()->ChangeState(GoToSchool::Instance());

		return true;
	}
	}

	return false;
}

//=========================================================================================================================================

GoToSchool* GoToSchool::Instance()
{
	static GoToSchool instance;

	return &instance;
}

void GoToSchool::Enter(Daughter* pDaughter)
{
	if (pDaughter->Location() != School)
	{
		std::cout << GetNameOfEntity(pDaughter->ID()) << ": �ʾ���. ���� �б� ������." << std::endl;

		pDaughter->ChangeLocation(School);
	}
}

void GoToSchool::Execute(Daughter* pDaughter)
{
	std::cout << GetNameOfEntity(pDaughter->ID()) << ": � ��" << std::endl;

	pDaughter->GetFSM()->ChangeState(StudyingAtSchool::Instance());
}

void GoToSchool::Exit(Daughter* pDaughter)
{
	std::cout << GetNameOfEntity(pDaughter->ID()) << ": �� ������ ������ ���ߴ�." << std::endl;
}

bool GoToSchool::OnMessage(Daughter* pDaughter, const Telegram& msg)
{
	return false;
}

//=========================================================================================================================================

StudyingAtSchool* StudyingAtSchool::Instance()
{
	static StudyingAtSchool instance;

	return &instance;
}

void StudyingAtSchool::Enter(Daughter* pDaughter)
{
	std::cout << GetNameOfEntity(pDaughter->ID()) << ": ���� ���� �ð��̳�." << std::endl;
}

void StudyingAtSchool::Execute(Daughter* pDaughter)
{
	std::cout << GetNameOfEntity(pDaughter->ID()) << ": " << pDaughter->GetPeriod() << "���� ���� ��" << std::endl;

	pDaughter->IncreasePeriod();

	if (pDaughter->GetPeriod() == 5)
		pDaughter->GetFSM()->ChangeState(EatLunchAtLunchroom::Instance());
	else if (pDaughter->GetPeriod() == 9)
		pDaughter->GetFSM()->ChangeState(GoToHome::Instance());
}

void StudyingAtSchool::Exit(Daughter* pDaughter)
{
	if (pDaughter->GetPeriod() == 5)
		std::cout << GetNameOfEntity(pDaughter->ID()) << ": ���� �ð��̳�. �� ������ ������.~" << std::endl;
	else if (pDaughter->GetPeriod() == 9)
	{
		pDaughter->ResetPeriod();

		std::cout << GetNameOfEntity(pDaughter->ID()) << ": �� �� �ð��̳�. ������!!!" << std::endl;
	}
}

bool StudyingAtSchool::OnMessage(Daughter* pDaughter, const Telegram& msg)
{
	return false;
}

//=========================================================================================================================================

EatLunchAtLunchroom* EatLunchAtLunchroom::Instance()
{
	static EatLunchAtLunchroom instance;

	return &instance;
}

void EatLunchAtLunchroom::Enter(Daughter* pDaughter)
{
	std::cout << GetNameOfEntity(pDaughter->ID()) << ": ������ �޴��� �����?" << std::endl;
}

void EatLunchAtLunchroom::Execute(Daughter* pDaughter)
{
	std::cout << GetNameOfEntity(pDaughter->ID()) << ": " << "�ϳɳɳ�" << std::endl;

	pDaughter->GetFSM()->RevertToPreviousState();
}

void EatLunchAtLunchroom::Exit(Daughter* pDaughter)
{
	std::cout << GetNameOfEntity(pDaughter->ID()) << ": ����. ��θ���." << std::endl;
}

bool EatLunchAtLunchroom::OnMessage(Daughter* pDaughter, const Telegram& msg)
{
	return false;
}

//=========================================================================================================================================

GoToHome* GoToHome::Instance()
{
	static GoToHome instance;

	return &instance;
}

void GoToHome::Enter(Daughter* pDaughter)
{
	if (pDaughter->Location() != Home)
	{
		std::cout << GetNameOfEntity(pDaughter->ID()) << ": ���� ���� ���ұ�? ����" << std::endl;

		pDaughter->ChangeLocation(Home);
	}
}

void GoToHome::Execute(Daughter* pDaughter)
{
	std::cout << GetNameOfEntity(pDaughter->ID()) << ": " << "�ϱ� ��" << std::endl;

	pDaughter->GetFSM()->ChangeState(DoSomethingAtHome::Instance());
}

void GoToHome::Exit(Daughter* pDaughter)
{
	std::cout << GetNameOfEntity(pDaughter->ID()) << ": ������, �𸣰ڴ�. �ϰ� ���� �ź��� ���� ��." << std::endl;
}

bool GoToHome::OnMessage(Daughter* pDaughter, const Telegram& msg)
{
	return false;
}

//=========================================================================================================================================

DoSomethingAtHome* DoSomethingAtHome::Instance()
{
	static DoSomethingAtHome instance;

	return &instance;
}

void DoSomethingAtHome::Enter(Daughter* pDaughter)
{
	std::cout << GetNameOfEntity(pDaughter->ID()) << ": �����, ������ �ұ�?" << std::endl;
}

void DoSomethingAtHome::Execute(Daughter* pDaughter)
{
	std::uniform_int_distribution<> uid(0, 1);

	switch (uid(dre))
	{
	case 0:
		std::cout << GetNameOfEntity(pDaughter->ID()) << ": " << "���� ��" << std::endl;
		break;
	case 1:
		std::cout << GetNameOfEntity(pDaughter->ID()) << ": " << "��� ��" << std::endl;
		break;
	}
}

void DoSomethingAtHome::Exit(Daughter* pDaughter)
{
}

bool DoSomethingAtHome::OnMessage(Daughter* pDaughter, const Telegram& msg)
{
	SetTextColor(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY);

	switch (msg.Msg)
	{
	case Msg_CookingFinished:

		std::cout << "Message handled by " << GetNameOfEntity(pDaughter->ID()) << " at time: " << Clock->GetCurrentTime() << std::endl;

		SetTextColor(FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY);

		std::cout << GetNameOfEntity(pDaughter->ID()) << ": ��, ��.~" << std::endl;;

		pDaughter->GetFSM()->ChangeState(EatDinnerAtHome::Instance());

		return true;
	}

	return false;
}

//=========================================================================================================================================

EatDinnerAtHome* EatDinnerAtHome::Instance()
{
	static EatDinnerAtHome instance;

	return &instance;
}

void EatDinnerAtHome::Enter(Daughter* pDaughter)
{
	std::cout << GetNameOfEntity(pDaughter->ID()) << ": ������ ������ �����?" << std::endl;
}

void EatDinnerAtHome::Execute(Daughter* pDaughter)
{
	std::cout << GetNameOfEntity(pDaughter->ID()) << ": " << "���� �������δ� �߲�~�� ��������." << std::endl;

	pDaughter->GetFSM()->ChangeState(SleepForNextDay::Instance());
}

void EatDinnerAtHome::Exit(Daughter* pDaughter)
{
	std::cout << GetNameOfEntity(pDaughter->ID()) << ": �߸Ծ����ϴ�." << std::endl;

	pDaughter->SetFatigue();
}

bool EatDinnerAtHome::OnMessage(Daughter* pDaughter, const Telegram& msg)
{
	return false;
}

//=========================================================================================================================================

SleepForNextDay* SleepForNextDay::Instance()
{
	static SleepForNextDay instance;

	return &instance;
}

void SleepForNextDay::Enter(Daughter* pDaughter)
{
	std::cout << GetNameOfEntity(pDaughter->ID()) << ": ���� �߱�?" << std::endl;
}

void SleepForNextDay::Execute(Daughter* pDaughter)
{
	if (!pDaughter->Asleep())
	{
		std::cout << GetNameOfEntity(pDaughter->ID()) << ": " << "����! �� ���." << std::endl;

		pDaughter->GetFSM()->ChangeState(GoToSchool::Instance());
	}
	else
	{
		pDaughter->DecreaseFatigue();

		std::cout << GetNameOfEntity(pDaughter->ID()) << ": " << "ZZZ..." << std::endl;
	}
}

void SleepForNextDay::Exit(Daughter* pDaughter)
{
	std::cout << GetNameOfEntity(pDaughter->ID()) << ": ���� �� ����?." << std::endl;
}

bool SleepForNextDay::OnMessage(Daughter* pDaughter, const Telegram& msg)
{
	return false;
}