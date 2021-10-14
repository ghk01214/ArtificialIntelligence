#include "SubwayDriver.h"

SubwayDriver::SubwayDriver(int id) : m_Location(Home), m_iCourseRepitition(0), m_iHunger(0), m_iFatigue(0), m_bEatLunch(false), BaseGameEntity(id)
{
	m_pStateMachine = new StateMachine<SubwayDriver>(this);
	m_pStateMachine->SetCurrentState(GoHomeAndSleepTilRested::Instance());
}

void SubwayDriver::Update()
{
	SetTextColor(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY);

	m_pStateMachine->Update();
}

bool SubwayDriver::Hunger() const
{
	if (m_iHunger >= HungerLevel)
		return true;

	return false;
}

bool SubwayDriver::GetOffWork() const
{
	if (m_iCourseRepitition >= MaxCourseLoop)
		return true;

	return false;
}

bool SubwayDriver::Fatigued() const
{
	if (m_iFatigue > TirednessThreshold)
		return true;

	return false;
}