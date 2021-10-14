#pragma once
#pragma warning (disable:4786)
#include <map>
#include <cassert>
#include <string>

class BaseGameEntity;

#define EntityMgr EntityManager::Instance()

class EntityManager
{
private:
	EntityManager() {}
	EntityManager(const EntityManager&);
	EntityManager& operator=(const EntityManager&);
public:
	static EntityManager* Instance();
	void            RegisterEntity(BaseGameEntity* NewEntity);
	BaseGameEntity* GetEntityFromID(int id) const;
	void            RemoveEntity(BaseGameEntity* pEntity);

private:
	typedef std::map<int, BaseGameEntity*> EntityMap;
private:
	EntityMap m_EntityMap;
};