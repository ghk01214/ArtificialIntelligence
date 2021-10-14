#include "Daughter.h"

Daughter::Daughter(int id) : m_Location(Home), m_iPeriod(1.0), m_iFatigue(0), BaseGameEntity(id)
{
	m_pStateMachine = new StateMachine<Daughter>(this);

	m_pStateMachine->SetCurrentState(SleepForNextDay::Instance());
	m_pStateMachine->SetGlobalState(DaughtersGlobalState::Instance());
}

void Daughter::Update()
{
	SetTextColor(FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY);

	m_pStateMachine->Update();
}

bool Daughter::Asleep() const
{
	if (m_iFatigue >= MaxFatigue)
		return true;

	return false;
}