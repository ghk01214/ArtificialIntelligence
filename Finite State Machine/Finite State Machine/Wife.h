#pragma once
#include <string>
#include "../Common/../Common/fsm/State.h"
#include "BaseGameEntity.h"
#include "Locations.h"
#include "WifeStates.h"
#include "../Common/misc/ConsoleUtils.h"
#include "SubwayDriver.h"
#include "../Common/fsm/StateMachine.h"
#include "../Common/misc/Utils.h"

class Wife : public BaseGameEntity
{
public:
	Wife(int id);
	~Wife() { delete m_pStateMachine; }
public:
	void          Update();
	virtual bool  HandleMessage(const Telegram& msg) { return m_pStateMachine->HandleMessage(msg); }
	StateMachine<Wife>* GetFSM() const { return m_pStateMachine; }
public:
	location_type Location() const { return m_Location; }
	void          ChangeLocation(location_type loc) { m_Location = loc; }
	bool          Cooking() const { return m_bCooking; }
	void          StartCooking(bool val) { m_bCooking = val; }

private:
	StateMachine<Wife>* m_pStateMachine;
	location_type   m_Location;
	bool            m_bCooking;
};