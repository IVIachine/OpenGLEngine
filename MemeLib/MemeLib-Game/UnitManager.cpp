#include <map>
#include <cassert>
#include "UnitManager.h"
#include "Unit.h"
#include "Game.h"
#include "ComponentManager.h"
#include "Graphics.h"

UnitID UnitManager::ms_nextUnitID = PLAYER_UNIT_ID + 1;
UnitManager* UnitManager::sp_instance = NULL;

using namespace std;

UnitManager::UnitManager(Uint32 maxSize)
	:m_pool(maxSize, sizeof(Unit))
{
}

UnitManager::~UnitManager()
{
	cleanup();
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


bool UnitManager::setup()
{
	return true;
}

void UnitManager::cleanup()
{

}


Unit* UnitManager::createUnit(
	const Sprite& sprite,
	bool shouldWrap,
	const TransformData& transformData,
	const PhysicsData& physicsData,
	const UnitID& id)
{
	Unit* pUnit = NULL;

	Byte* ptr = m_pool.allocateObject();
	if (ptr != NULL)
	{
		//create unit
		pUnit = new (ptr)Unit(sprite);//placement new

		UnitID theID = id;
		if (theID == INVALID_UNIT_ID)
		{
			theID = ms_nextUnitID;
			ms_nextUnitID++;
		}

		//place in map
		m_unitMap[theID] = pUnit;

		//assign id and increment nextID counter
		pUnit->mID = theID;

		//create some COMPONENT_MANAGER
		ComponentManager* pComponentManager = COMPONENTS;
		pUnit->mTransformComponentID = pComponentManager->allocateTransformComponent(transformData, shouldWrap);
		pUnit->mPhysicsComponentID = pComponentManager->allocatePhysicsComponent(pUnit->mTransformComponentID, physicsData);
		pUnit->mSteeringComponentID = pComponentManager->allocateSteeringComponent(pUnit->mPhysicsComponentID);

		//set max's
		pUnit->mMaxSpeed = PHYS_MAX_VEL;
		pUnit->mMaxAcc = PHYS_MAX_ACC;
		pUnit->mMaxRotAcc = PHYS_MAX_ROT_ACC;
		pUnit->mMaxRotVel = PHYS_MAX_ROT_VEL;

		std::cout << "unit created\n";
	}

	return pUnit;
}

Unit* UnitManager::createPlayerUnit(
	const Sprite& sprite, bool shouldWrap, const TransformData& transformData, const PhysicsData& physicsData)
{
	return createUnit(
		sprite,
		shouldWrap,
		transformData,
		physicsData,
		PLAYER_UNIT_ID);
}

Unit* UnitManager::createRandomUnit(const Sprite& sprite)
{
	int width = 6;
	int height = 3;

	float posX = float(rand() % width);
	float posY = float(rand() % height);
	float velX = float(rand() % 50 - 25);
	float velY = float(rand() % 40 - 20);

	TransformData tData = TransformData(Vector2(posX, posY), 0);
	PhysicsData pData = PhysicsData(Vector2(velX, velY), Vector2(0.1f, 0.1f), 0.1f, 0.05f);
	Unit* p_unit = createUnit(
		sprite,
		true,
		tData,
		pData);

	if (p_unit != NULL)
	{
		Vector2 seekPos(float(GRAPHICS->getWidth()) / 2.f, float(GRAPHICS->getHeight()) / 2);
		p_unit->setSteering(Steering::SEEK, seekPos);
	}

	//p_unit->getTransformComponent()->setPosition({ 5, 0 });

	return p_unit;
}



Unit* UnitManager::getUnit(const UnitID& id) const
{
	auto it = m_unitMap.find(id);
	if (it != m_unitMap.end())//found?
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
	auto it = m_unitMap.find(id);
	if (it != m_unitMap.end())//found?
	{
		Unit* pUnit = it->second;//hold for later

								 //remove from map
		m_unitMap.erase(it);

		//remove COMPONENT_MANAGER
		ComponentManager* pComponentManager = COMPONENTS;
		pComponentManager->deallocatePhysicsComponent(pUnit->mPhysicsComponentID);
		pComponentManager->deallocateTransformComponent(pUnit->mTransformComponentID);
		pComponentManager->deallocateSteeringComponent(pUnit->mSteeringComponentID);

		//call destructor
		pUnit->~Unit();

		//free the object in the pool
		m_pool.freeObject((Byte*)pUnit);
	}
}

void UnitManager::deleteRandomUnit()
{
	if (m_unitMap.size() == 0)
		return;

	size_t index = rand() % m_unitMap.size();
	if (getPlayerUnit() != NULL)
	{
		while (index == PLAYER_UNIT_ID)
		{
			index = rand() % m_unitMap.size();
		}
	}

	size_t count = 0;
	for (auto it = m_unitMap.begin(); it != m_unitMap.end(); ++it, count++)
	{
		if (count == index)
		{
			deleteUnit(it->first);

			break;
		}
	}
}


void UnitManager::drawAll() const
{
	for (auto it = m_unitMap.begin(); it != m_unitMap.end(); ++it)
	{
		it->second->draw();
	}
}

void UnitManager::updateAll(float elapsedTime)
{
	for (auto it = m_unitMap.begin(); it != m_unitMap.end(); ++it)
	{
		it->second->update(elapsedTime);
	}
}


std::vector<Unit*> UnitManager::toList()
{
	std::vector<Unit*> list;

	for (auto it = m_unitMap.begin(); it != m_unitMap.end(); ++it)
	{
		list.push_back(it->second);
	}

	return list;
}

std::vector<Unit*> UnitManager::findUnitsInRadius(Vector2 pos, float radius)
{
	return findUnitsInRadius(&toList(), pos, radius);
}

std::vector<Unit*> UnitManager::findUnitsInRadius(std::vector<Unit*>* source, Vector2 pos, float radius)
{
	std::vector<Unit*> result;

	for (auto it = source->begin(); it != source->end(); ++it)
	{
		if (Vector2::distance(pos, (*it)->getPosition()) <= radius)
		{
			result.push_back(*it);
		}
	}

	return result;
}