#pragma once
#include <string>
#include "../../Common/fsm/State.h"
#include "BaseGameEntity.h"
#include "Locations.h"
#include "DaughterStates.h"
#include "../../Common/misc/ConsoleUtils.h"
#include "SubwayDriver.h"
#include "../../Common/fsm/StateMachine.h"
#include "../../Common/misc/Utils.h"

const int MaxFatigue{ 7 };

class Daughter : public BaseGameEntity
{
public:
	Daughter(int id);
	~Daughter() { delete m_pStateMachine; }
public:
	void          Update();
	virtual bool  HandleMessage(const Telegram& msg) { return m_pStateMachine->HandleMessage(msg); }
	StateMachine<Daughter>* GetFSM() const { return m_pStateMachine; }
public:
	location_type Location() const { return m_Location; }
	void          ChangeLocation(location_type loc) { m_Location = loc; }
	
	void          DecreaseFatigue() { m_iFatigue -= 1; }
	void		  DecreasesHomeworks() { m_iHomeworks -= 1; }

	void		  IncreasePeriod() { m_iPeriod += 0.5; }
	void		  ResetPeriod() { m_iPeriod = 1.0; }
	void		  GoHome() { m_iPeriod = 0; }
	bool		  Asleep() const;
public:
	void          SetFatigue() { m_iFatigue = 10; }
	int			  GetPeriod() { return m_iPeriod; }

private:
	StateMachine<Daughter>* m_pStateMachine;
	location_type   m_Location;
	float			m_iPeriod;
	int				m_iHomeworks;
	int				m_iFatigue;
};