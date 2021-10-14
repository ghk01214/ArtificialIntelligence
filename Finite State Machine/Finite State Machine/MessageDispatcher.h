#pragma once
#pragma warning (disable:4786)

#include <set>
#include "../../Common/misc/ConsoleUtils.h"
#include "../../Common/messaging/Telegram.h"

class BaseGameEntity;

const double SEND_MSG_IMMEDIATELY{ 0.0f };
const int   NO_ADDITIONAL_INFO{ 0 };

#define Dispatch MessageDispatcher::Instance()

class MessageDispatcher
{
private:
	void Discharge(BaseGameEntity* pReceiver, const Telegram& msg);
	MessageDispatcher() {}
	MessageDispatcher(const MessageDispatcher&);
	MessageDispatcher& operator=(const MessageDispatcher&);
public:
	static MessageDispatcher* Instance();
	void DispatchMessage(double  delay, int sender, int receiver, int msg, void* ExtraInfo);
	void DispatchDelayedMessages();

private:
	std::set<Telegram> PriorityQ;
};