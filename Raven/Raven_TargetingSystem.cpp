#include "Raven_TargetingSystem.h"
#include "Raven_Bot.h"
#include "Raven_SensoryMemory.h"


//-------------------------------- ctor ---------------------------------------
//-----------------------------------------------------------------------------
Raven_TargetingSystem::Raven_TargetingSystem(Raven_Bot* owner) :m_pOwner(owner),
m_pCurrentTarget(0)
{}



//----------------------------- Update ----------------------------------------

//-----------------------------------------------------------------------------
void Raven_TargetingSystem::UpdateByDistance()
{
	double ClosestDistSoFar = MaxDouble;
	m_pCurrentTarget = 0;

	//grab a list of all the opponents the owner can sense
	// 가장 최근에 감지된 봇들의 목록
	std::list<Raven_Bot*> SensedBots;
	SensedBots = m_pOwner->GetSensoryMem()->GetListOfRecentlySensedOpponents();

	std::list<Raven_Bot*>::const_iterator curBot = SensedBots.begin();
	for (curBot; curBot != SensedBots.end(); ++curBot)
	{
		//make sure the bot is alive and that it is not the owner
		if ((*curBot)->isAlive() && (*curBot != m_pOwner))
		{
			double dist = Vec2DDistanceSq((*curBot)->Pos(), m_pOwner->Pos());

			if (dist < ClosestDistSoFar)
			{
				ClosestDistSoFar = dist;
				m_pCurrentTarget = *curBot;
			}
		}
	}
}

//==================================================
void Raven_TargetingSystem::UpdateByHealth()
{
	int health = MaxInt;
	m_pCurrentTarget = 0;

	auto SensedBots = m_pOwner->GetSensoryMem()->GetListOfRecentlySensedOpponents();

	for (auto curBot = SensedBots.begin(); curBot != SensedBots.end(); ++curBot)
	{
		if (*curBot)->isAlive())
		{
			int enemyHealth = m_pOwner->GetSensoryMem()->GetEnemyHealth(*curBot);

			// 봇이 기억하고 있는 체력이 가장 낮은 적을 타겟으로 한다
			if (enemyHealth < health)
			{
				health = enemyHealth;
				m_pCurrentTarget = *curBot;
			}
		}
	}
}

void Raven_TargetingSystem::UpdateByDamaged()
{
	int dam = (std::numeric_limits<int>::min)();
	m_pCurrentTarget = 0;

	auto SensedBots = m_pOwner->GetSensoryMem()->GetListOfRecentlySensedOpponents();

	for (auto curBot = SensedBots.begin(); curBot != SensedBots.end(); ++curBot)
	{
		if ((*curBot)->isAlive())
		{
			auto damage = m_pOwner->GetSensoryMem()->GetDamaged(*curBot);

			if (damage > dam)
			{
				dam = damage;
				m_pCurrentTarget = *curBot;
			}
		}
	}
}
//==================================================

bool Raven_TargetingSystem::isTargetWithinFOV() const
{
	return m_pOwner->GetSensoryMem()->isOpponentWithinFOV(m_pCurrentTarget);
}

bool Raven_TargetingSystem::isTargetShootable() const
{
	return m_pOwner->GetSensoryMem()->isOpponentShootable(m_pCurrentTarget);
}

Vector2D Raven_TargetingSystem::GetLastRecordedPosition() const
{
	return m_pOwner->GetSensoryMem()->GetLastRecordedPositionOfOpponent(m_pCurrentTarget);
}

double Raven_TargetingSystem::GetTimeTargetHasBeenVisible() const
{
	return m_pOwner->GetSensoryMem()->GetTimeOpponentHasBeenVisible(m_pCurrentTarget);
}

double Raven_TargetingSystem::GetTimeTargetHasBeenOutOfView() const
{
	return m_pOwner->GetSensoryMem()->GetTimeOpponentHasBeenOutOfView(m_pCurrentTarget);
}
