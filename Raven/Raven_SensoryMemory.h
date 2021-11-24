#ifndef RAVEN_SENSORY_SYSTEM_H
#define RAVEN_SENSORY_SYSTEM_H
#pragma warning (disable:4786)
//-----------------------------------------------------------------------------
//
//  Name:
//
//  Author: Mat Buckland (ai-junkie.com)
//
//  Desc:
//
//-----------------------------------------------------------------------------
#include <map>
#include <list>
#include "2d/vector2d.h"

class Raven_Bot;


class MemoryRecord
{
public:

	//records the time the opponent was last sensed (seen or heard). This
	//is used to determine if a bot can 'remember' this record or not. 
	//(if CurrentTime() - m_dTimeLastSensed is greater than the bot's
	//memory span, the data in this record is made unavailable to clients)
	// 마지막으로 적이 감지된 시간
	double       fTimeLastSensed;

	//it can be useful to know how long an opponent has been visible. This 
	//variable is tagged with the current time whenever an opponent first becomes
	//visible. It's then a simple matter to calculate how long the opponent has
	//been in view (CurrentTime - fTimeBecameVisible)
	// 처음 적이 보인 시간
	double       fTimeBecameVisible;

	//it can also be useful to know the last time an opponent was seen
	// 마지막으로 적이 보인 시간
	double       fTimeLastVisible;

	//a vector marking the position where the opponent was last sensed. This can
	// be used to help hunt down an opponent if it goes out of view
	// 적이 마지막으로 감지된 좌표
	Vector2D    vLastSensedPosition;

	//set to true if opponent is within the field of view of the owner
	// 적이 봇의 시야에 들어와있는지 판단
	bool        bWithinFOV;

	//set to true if there is no obstruction between the opponent and the owner, 
	//permitting a shot.
	// 적과 봇 사이에 장애물이 없으면 쏠 수 있는지 여부
	bool        bShootable;

	// 다른 봇들의 피격 데미지 정보를 저장
	//std::list<int> lEnemyHealth;

	MemoryRecord() : fTimeLastSensed(-999),
		fTimeBecameVisible(-999),
		fTimeLastVisible(0),
		bWithinFOV(false),
		bShootable(false)
		//lEnemyHealth(3, 0)
	{}
};



class Raven_SensoryMemory
{
private:

	using MemoryMap = std::map<Raven_Bot*, MemoryRecord>;

private:

	//the owner of this instance
	//해당 인스턴스의 봇
	Raven_Bot* m_pOwner;

	//this container is used to simulate memory of sensory events. A MemoryRecord
	//is created for each opponent in the environment. Each record is updated 
	//whenever the opponent is encountered. (when it is seen or heard)
	MemoryMap  m_MemoryMap;

	//a bot has a memory span equivalent to this value. When a bot requests a 
	//list of all recently sensed opponents this value is used to determine if 
	//the bot is able to remember an opponent or not.
	double      m_dMemorySpan;

	//this methods checks to see if there is an existing record for pBot. If
	//not a new MemoryRecord record is made and added to the memory map.(called
	//by UpdateWithSoundSource & UpdateVision)
	void       MakeNewRecordIfNotAlreadyPresent(Raven_Bot* pBot);

public:

	Raven_SensoryMemory(Raven_Bot* owner, double MemorySpan);

	//this method is used to update the memory map whenever an opponent makes
	//a noise
	void     UpdateWithSoundSource(Raven_Bot* pNoiseMaker);

	//this removes a bot's record from memory
	void     RemoveBotFromMemory(Raven_Bot* pBot);

	//this method iterates through all the opponents in the game world and 
	//updates the records of those that are in the owner's FOV
	void     UpdateVision();

	bool     isOpponentShootable(Raven_Bot* pOpponent) const;
	bool     isOpponentWithinFOV(Raven_Bot* pOpponent) const;
	Vector2D GetLastRecordedPositionOfOpponent(Raven_Bot* pOpponent) const;
	double    GetTimeOpponentHasBeenVisible(Raven_Bot* pOpponent) const;
	double    GetTimeSinceLastSensed(Raven_Bot* pOpponent) const;
	double    GetTimeOpponentHasBeenOutOfView(Raven_Bot* pOpponent) const;

	//this method returns a list of all the opponents that have had their
	//records updated within the last m_dMemorySpan seconds.
	std::list<Raven_Bot*> GetListOfRecentlySensedOpponents() const;

	void     RenderBoxesAroundRecentlySensed() const;

};


#endif