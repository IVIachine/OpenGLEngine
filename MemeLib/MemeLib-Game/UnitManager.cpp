#include <map>

#include "UnitManager.h"
#include "Unit.h"
#include "Game.h"
#include "GameApp.h"
#include "Graphics.h"

UnitID UnitManager::msNextUnitID = PLAYER_UNIT_ID + 1;
UnitManager* UnitManager::sp_instance = NULL;

using namespace std;

bool UnitManager::setup()
{
	return true;
}

UnitManager::UnitManager(Uint32 maxSize)
	:mPool(maxSize, sizeof(Unit))
{
}

UnitManager* UnitManager::getInstance()
{
	assert(sp_instance != NULL);
	return sp_instance;
}

void UnitManager::disposeInstance()
{
	delete sp_instance;
	sp_instance = NULL;
}

UnitManager* UnitManager::createInstance(Uint32 maxSize)
{
	sp_instance = new UnitManager(maxSize);
	return getInstance();
}

Unit* UnitManager::createUnit(const Sprite& sprite, NavigationMesh* graph, bool shouldWrap, const PositionData& posData /*= ZERO_POSITION_DATA*/, const PhysicsData& physicsData /*= ZERO_PHYSICS_DATA*/, const UnitID& id)
{
	Unit* pUnit = NULL;

	Byte* ptr = mPool.allocateObject();
	if (ptr != NULL)
	{
		//create unit
		pUnit = new (ptr)Unit(sprite, graph);//placement new

		UnitID theID = id;
		if (theID == INVALID_UNIT_ID)
		{
			theID = msNextUnitID;
			msNextUnitID++;
		}

		//place in map
		mUnitMap[theID] = pUnit;

		//assign id and increment nextID counter
		pUnit->mID = theID;

		//create some components
		ComponentManager* pComponentManager = COMPONENTS;
		pUnit->mPositionComponentID = pComponentManager->allocatePositionComponent(posData,shouldWrap);
		pUnit->mPhysicsComponentID = pComponentManager->allocatePhysicsComponent(pUnit->mPositionComponentID, physicsData);
		pUnit->mSteeringComponentID = pComponentManager->allocateSteeringComponent(pUnit->mPhysicsComponentID);

		//set max's
		pUnit->mMaxSpeed = MAX_SPEED;
		pUnit->mMaxAcc = MAX_ACC;
		pUnit->mMaxRotAcc = MAX_ROT_ACC;
		pUnit->mMaxRotVel = MAX_ROT_VEL;

	}

	return pUnit;
}


Unit* UnitManager::getUnit(const UnitID& id) const
{
	auto it = mUnitMap.find(id);
	if (it != mUnitMap.end())//found?
	{
		return it->second;
	}
	else
	{
		return NULL;
	}
}

void UnitManager::deleteUnit(const UnitID& id)
{
	auto it = mUnitMap.find(id);
	if (it != mUnitMap.end())//found?
	{
		Unit* pUnit = it->second;//hold for later

		//remove from map
		mUnitMap.erase(it);

		//remove components
		ComponentManager* pComponentManager = COMPONENTS;

		pComponentManager->deallocatePhysicsComponent(pUnit->mPhysicsComponentID);
		pComponentManager->deallocatePositionComponent(pUnit->mPositionComponentID);
		pComponentManager->deallocateSteeringComponent(pUnit->mSteeringComponentID);

		//call destructor
		pUnit->~Unit();

		//free the object in the pool
		mPool.freeObject((Byte*)pUnit);
	}
}

void UnitManager::deleteRandomUnit()
{
	Uint32 target = rand() % mUnitMap.size();
	Uint32 cnt = 0;
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
				deleteUnit(it->first);
				break;
			}
			else
			{
				deleteRandomUnit();
			}
		}
	}
}

void UnitManager::drawAll() const
{
	for (auto it = mUnitMap.begin(); it != mUnitMap.end(); ++it)
	{
		it->second->draw();
	}
}

void UnitManager::updateAll(float elapsedTime)
{
	for (auto it = mUnitMap.begin(); it != mUnitMap.end(); ++it)
	{
		it->second->update(elapsedTime);
	}
}
