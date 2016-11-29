#include <cassert>
#include "ComponentManager.h"
#include "Component.h"
#include "PositionComponent.h"
#include "PhysicsComponent.h"
#include "SteeringComponent.h"


ComponentID ComponentManager::ms_nextPositionComponentID = 0;
ComponentID ComponentManager::ms_nextPhysicsComponentID = 0;
ComponentID ComponentManager::ms_nextSteeringComponentID = 0;
ComponentManager* ComponentManager::sp_instance = NULL;

using namespace std;


ComponentManager::ComponentManager(Uint32 maxSize) : 
	m_positionPool(maxSize, sizeof(PositionComponent)), 
	m_physicsPool(maxSize, sizeof(PhysicsComponent)), 
	m_steeringPool(maxSize, sizeof(SteeringComponent))
{
}

ComponentManager::~ComponentManager()
{
	clear();
}


ComponentManager* ComponentManager::getInstance()
{
	assert(sp_instance != NULL);
	return sp_instance;
}

void ComponentManager::disposeInstance()
{
	delete sp_instance;
	sp_instance = NULL;
}

ComponentManager* ComponentManager::createInstance(Uint32 maxSize)
{
	sp_instance = new ComponentManager(maxSize);
	return getInstance();
}


bool ComponentManager::setup()
{
	return true;
}

void ComponentManager::clear()
{
	//clear maps
	m_positionCOMPONENT_MANAGER.clear();
	m_physicsCOMPONENT_MANAGER.clear();
	m_steeringCOMPONENT_MANAGER.clear();

	//reset memory pools
	m_positionPool.reset();
	m_physicsPool.reset();
	m_steeringPool.reset();
}


PositionComponent* ComponentManager::getPositionComponent(const ComponentID& id)
{
	return m_positionCOMPONENT_MANAGER.getData(id);
}

ComponentID ComponentManager::allocatePositionComponent(const PositionData& data, bool shouldWrap)
{
	ComponentID newID = INVALID_COMPONENT_ID;

	Byte* ptr = m_positionPool.allocateObject();
	if (ptr != NULL)
	{
		newID = ms_nextPositionComponentID;
		PositionComponent* pComponent = new (ptr)PositionComponent(newID, shouldWrap);
		pComponent->setData(data);
		m_positionCOMPONENT_MANAGER.addData(newID, pComponent);
		ms_nextPositionComponentID++;//increment id
	}

	return newID;
}

bool ComponentManager::deallocatePositionComponent(const ComponentID& id)
{
	return m_positionCOMPONENT_MANAGER.erase(id);
}


PhysicsComponent* ComponentManager::getPhysicsComponent(const ComponentID& id)
{
	return m_physicsCOMPONENT_MANAGER.getData(id);
}

ComponentID ComponentManager::allocatePhysicsComponent(const ComponentID& positionComponentID, const PhysicsData& data)
{
	ComponentID newID = INVALID_COMPONENT_ID;

	Byte* ptr = m_physicsPool.allocateObject();
	if (ptr != NULL)
	{
		newID = ms_nextPhysicsComponentID;
		PhysicsComponent* pComponent = new (ptr)PhysicsComponent(newID, positionComponentID);
		pComponent->setData(data);
		m_physicsCOMPONENT_MANAGER.addData(newID, pComponent);
		ms_nextPhysicsComponentID++;//increment id
	}

	return newID;
}

bool ComponentManager::deallocatePhysicsComponent(const ComponentID& id)
{
	return m_physicsCOMPONENT_MANAGER.erase(id);
}


SteeringComponent* ComponentManager::getSteeringComponent(const ComponentID& id)
{
	return m_steeringCOMPONENT_MANAGER.getData(id);
}

ComponentID ComponentManager::allocateSteeringComponent(const ComponentID& physicsComponentID, const SteeringData& data)
{
	ComponentID newID = INVALID_COMPONENT_ID;

	Byte* ptr = m_steeringPool.allocateObject();
	if (ptr != NULL)
	{
		newID = ms_nextSteeringComponentID;
		SteeringComponent* pComponent = new (ptr)SteeringComponent(newID, physicsComponentID);
		pComponent->setData(data);
		m_steeringCOMPONENT_MANAGER.addData(newID, pComponent);
		ms_nextSteeringComponentID++;//increment id
	}

	return newID;
}

bool ComponentManager::deallocateSteeringComponent(const ComponentID& id)
{
	return m_steeringCOMPONENT_MANAGER.erase(id);
}


const float ELAPSED_TIME_PHYSICS_MULT = 1.0f;

void ComponentManager::update(float elapsedTime)
{
	updateSteering(elapsedTime*ELAPSED_TIME_PHYSICS_MULT);
	updatePhysics(elapsedTime*ELAPSED_TIME_PHYSICS_MULT);
}

void ComponentManager::updatePhysics(float elapsedTime)
{
	for (auto& it : m_physicsCOMPONENT_MANAGER.getData())
	{
		PhysicsComponent* pPhysics = it.second;
		assert(pPhysics != NULL);
		PositionComponent* pPosition = getPositionComponent(pPhysics->getID());
		assert(pPosition != NULL);
		pPhysics->integrate(*pPosition, elapsedTime);
	}
}

void ComponentManager::updateSteering(float elapsedTime)
{
	for (auto& it : m_steeringCOMPONENT_MANAGER.getData())
	{
		SteeringComponent* pSteering = it.second;
		assert(pSteering != NULL);
		PhysicsComponent* pPhysics = getPhysicsComponent(pSteering->getID());
		assert(pPhysics != NULL);
		pSteering->applySteering(*pPhysics);
	}

}