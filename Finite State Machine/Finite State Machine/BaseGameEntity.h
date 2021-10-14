#pragma once
#include <string>
#include "../../Common/messaging/Telegram.h"

class BaseGameEntity
{
private:
	void SetID(int val);
public:
	BaseGameEntity(int id) { SetID(id); }
	virtual ~BaseGameEntity() {}
public:
	virtual void  Update() = 0;
	virtual bool  HandleMessage(const Telegram& msg) = 0;
	int           ID() const { return m_ID; }

private:
	int         m_ID;
	static int  m_iNextValidID;
};