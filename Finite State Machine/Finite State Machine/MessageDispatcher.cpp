#include "MessageDispatcher.h"
#include "BaseGameEntity.h"
#include "../Common/Time/CrudeTimer.h"
#include "EntityManager.h"
#include "Locations.h"
#include "MessageTypes.h"
#include "EntityNames.h"

#include <iostream>

//using std::set;

#ifdef TEXTOUTPUT
#include <fstream>
extern std::ofstream os;
#define std::cout os
#endif

MessageDispatcher* MessageDispatcher::Instance()
{
	static MessageDispatcher instance;

	return &instance;
}

void MessageDispatcher::Discharge(BaseGameEntity* pReceiver, const Telegram& telegram)
{
	if (!pReceiver->HandleMessage(telegram))
		std::cout << "Message not handled" << std::endl;
}

void MessageDispatcher::DispatchMessage(double  delay, int sender, int receiver, int msg, void* ExtraInfo)
{
	SetTextColor(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY);

	BaseGameEntity* pSender{ EntityMgr->GetEntityFromID(sender) };
	BaseGameEntity* pReceiver{ EntityMgr->GetEntityFromID(receiver) };

	if (pReceiver == NULL)
	{
		std::cout << "Warning! No Receiver with ID of " << receiver << " found" << std::endl;

		return;
	}

	Telegram telegram(0, sender, receiver, msg, ExtraInfo);
                    
	if (delay <= 0.0f)
	{
		std::cout << "Instant telegram dispatched at time: " << Clock->GetCurrentTime()
			<< " by " << GetNameOfEntity(pSender->ID()) << " for " << GetNameOfEntity(pReceiver->ID())
			<< ". Msg is " << MsgToStr(msg) << std::endl;

		Discharge(pReceiver, telegram);
	}
	else
	{
		double CurrentTime{ Clock->GetCurrentTime() };

		telegram.DispatchTime = CurrentTime + delay;

		PriorityQ.insert(telegram);

		std::cout << "Delayed telegram from " << GetNameOfEntity(pSender->ID()) << " recorded at time "
			<< Clock->GetCurrentTime() << " for " << GetNameOfEntity(pReceiver->ID())
			<< ". Msg is " << MsgToStr(msg) << std::endl;
	}
}

void MessageDispatcher::DispatchDelayedMessages()
{
	SetTextColor(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY);

	double CurrentTime{ Clock->GetCurrentTime() };

	while (!PriorityQ.empty() && (PriorityQ.begin()->DispatchTime < CurrentTime) && (PriorityQ.begin()->DispatchTime > 0))
	{
		const Telegram& telegram{ *PriorityQ.begin() };

		BaseGameEntity* pReceiver{ EntityMgr->GetEntityFromID(telegram.Receiver) };

		std::cout << "Queued telegram ready for dispatch: Sent to "
			<< GetNameOfEntity(pReceiver->ID()) << ". Msg is " << MsgToStr(telegram.Msg) << std::endl;

		Discharge(pReceiver, telegram);

		PriorityQ.erase(PriorityQ.begin());
	}
}