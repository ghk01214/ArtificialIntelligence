#include "Wife.h"

Wife::Wife(int id) : m_Location(Home), m_bCooking(false), BaseGameEntity(id)
{
	m_pStateMachine = new StateMachine<Wife>(this);

	m_pStateMachine->SetCurrentState(DoHouseWork::Instance());
	m_pStateMachine->SetGlobalState(WifesGlobalState::Instance());
}

void Wife::Update()
{
	SetTextColor(FOREGROUND_GREEN | FOREGROUND_INTENSITY);

	m_pStateMachine->Update();
}