#pragma once
#include <string>
#include <cassert>
#include <iostream>
#include "BaseGameEntity.h"
#include "Locations.h"
#include "../Common/misc/ConsoleUtils.h"
#include "SubwayDriverStates.h"
#include "../Common/fsm/StateMachine.h"

template <class entity_type> class State;

struct Telegram;

const int MaxCourseLoop{ 10 };
const int HungerLevel{ 5 };
const int SmallTiredness{ 3 };
const int TirednessThreshold{ 5 };

class SubwayDriver : public BaseGameEntity
{
public:
	SubwayDriver(int id);
	~SubwayDriver() { delete m_pStateMachine; }
public:
	void Update();
	virtual bool  HandleMessage(const Telegram& msg) { return m_pStateMachine->HandleMessage(msg); }
	StateMachine<SubwayDriver>* GetFSM() const { return m_pStateMachine; }
public:
	location_type Location() const { return m_Location; }
	void          ChangeLocation(location_type loc) { m_Location = loc; }

	void		  AddDriveTimes() { m_iCourseRepitition += 1; }
	void		  EatLunch(bool eat) { m_bEatLunch = eat; }
	void		  FillingFull() { m_iHunger = 0; }
	void          DecreaseFatigue() { m_iFatigue -= 1; }
	void          IncreaseFatigue() { m_iFatigue += 1; }
	void          DecreaseHunger() { m_iHunger -= 1; }
	void          IncreaseHunger() { m_iHunger += 1; }

	bool		  DangerForDriving() { return m_iFatigue >= SmallTiredness; }
	
	bool		  AteLunch() const { return m_bEatLunch; }
	bool          Fatigued() const;
	bool          Hunger() const;
	bool		  GetOffWork() const;
public:
	int			  GetFatigue() const { return m_iFatigue; }

private:
	StateMachine<SubwayDriver>* m_pStateMachine;
	location_type         m_Location;
	int					  m_iCourseRepitition;
	int					  m_iHunger;
	int                   m_iFatigue;
	bool				  m_bEatLunch;
};