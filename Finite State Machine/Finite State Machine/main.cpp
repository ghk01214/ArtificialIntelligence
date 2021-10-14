#include <fstream>
#include <time.h>

#include "Locations.h"
#include "SubwayDriver.h"
#include "Wife.h"
#include "Daughter.h"
#include "EntityManager.h"
#include "MessageDispatcher.h"
#include "../Common/../Common/misc/ConsoleUtils.h"
#include "EntityNames.h"

std::ofstream os;

int main()
{
#ifdef TEXTOUTPUT
	os.open("output.txt");
#endif
	SetTextColor(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
	std::cout << "2017182004 ±è°ÇÈ£" << std::endl;

	SubwayDriver* Jeff{ new SubwayDriver(ent_Jeff) };
	Wife* Sam{ new Wife(ent_Sam) };
	Daughter* Eris{ new Daughter(ent_Eris) };

	EntityMgr->RegisterEntity(Jeff);
	EntityMgr->RegisterEntity(Sam);
	EntityMgr->RegisterEntity(Eris);

	for (int i = 0; i < 30; ++i)
	{
		Jeff->Update();
		Sam->Update();
		Eris->Update();

		Dispatch->DispatchDelayedMessages();

		Sleep(800);
	}

	delete Jeff;
	delete Sam;
	delete Eris;

	PressAnyKeyToContinue();
}