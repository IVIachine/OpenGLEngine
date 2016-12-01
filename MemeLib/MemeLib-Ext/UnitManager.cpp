#include <map>

#include "UnitManager.h"
#include "Unit.h"
#include "Game.h"
#include "Graphics.h"
#include "EventSystem.h"
#include "ChangeTargetEvent.h"
#include "BeginPathingEvent.h"
#include "ComponentManager.h"
#include "GameObjectManager.h"

//GameObjectID UnitManager::msNextUnitID = PLAYER_UNIT_ID + 1;
UnitManager* UnitManager::sp_instance = NULL;

using namespace std;

UnitManager::UnitManager(size_t maxSize)
{
	EVENT_SYSTEM->addListener(PATH_EVENT, this);
	EVENT_SYSTEM->addListener(TARGET_EVENT, this);
}


bool UnitManager::setup()
{
	return true;
}


Unit* UnitManager::createUnit(
	const Sprite& sprite, 
	NavMesh* graph,
	float health,
	float damageRadius,
	float damage,
	bool shouldWrap, 
	const PositionData& posData, 
	const PhysicsData& physicsData)
{
	Unit* pUnit = OBJECT_MANAGER->create<Unit>(new Unit(sprite, graph, health, damageRadius, damage));

	if (pUnit)
	{
		mUnitMap[pUnit->getID()] = pUnit;

		//create some components
		pUnit->mPositionComponentID = COMPONENTS->allocatePositionComponent(posData,shouldWrap);
		pUnit->mPhysicsComponentID = COMPONENTS->allocatePhysicsComponent(pUnit->mPositionComponentID, physicsData);
		pUnit->mSteeringComponentID = COMPONENTS->allocateSteeringComponent(pUnit->mPhysicsComponentID);

		//set max's
		pUnit->mMaxSpeed = MAX_SPEED;
		pUnit->mMaxAcc = MAX_ACC;
		pUnit->mMaxRotAcc = MAX_ROT_ACC;
		pUnit->mMaxRotVel = MAX_ROT_VEL;
	}

	return pUnit;
}

Unit* UnitManager::getUnit(const GameObjectID& id) const
{
	return OBJECT_MANAGER->findByID<Unit>(id);
}

bool UnitManager::deleteUnit(const GameObjectID& id)
{
	if (Unit* pUnit = OBJECT_MANAGER->findByID<Unit>(id))
	{
		//remove components
		ComponentManager* pComponentManager = COMPONENTS;

		pComponentManager->deallocatePhysicsComponent(pUnit->mPhysicsComponentID);
		pComponentManager->deallocatePositionComponent(pUnit->mPositionComponentID);
		pComponentManager->deallocateSteeringComponent(pUnit->mSteeringComponentID);

		OBJECT_MANAGER->removeByID(id);

		return true;
	}

	return false;
}

void UnitManager::deleteRandomUnit()
{
	size_t target = rand() % mUnitMap.size();
	size_t cnt = 0;
	if (mUnitMap.size() <= 1)
	{
		return;
	}
	for (auto it = mUnitMap.begin(); it != mUnitMap.end(); ++it, cnt++)
	{
		if (cnt == target)
		{
			if (it->first != NULL)
			{
				OBJECT_MANAGER->removeByID(it->first);
				break;
			}
			else
			{
				deleteRandomUnit();
			}
		}
	}
}

void UnitManager::deleteAll()
{
	if (mUnitMap.size() > 0)
	{
		for (auto& pair : mUnitMap)
		{
			deleteUnit(pair.first);
		}

		mUnitMap.clear();
	}
}


void UnitManager::handleEvent(const Event & ev)
{
	if (ev.getType() == PATH_EVENT)
	{
		Unit* tmp = OBJECT_MANAGER->findByID<Unit>(Unit::getPlayerID());
		tmp->findPath(tmp->getTarget());
	}
	else if (ev.getType() == TARGET_EVENT)
	{
		const ChangeTargetEvent& changeEvent = static_cast<const ChangeTargetEvent&>(ev);
		for (std::map<GameObjectID, Unit*>::iterator MapItor = mUnitMap.begin(); MapItor != mUnitMap.end(); ++MapItor)
		{
			MapItor->second->changeTarg(changeEvent.getTarg());
		}
	}
}