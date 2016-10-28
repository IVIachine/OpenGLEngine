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


ComponentManager::ComponentManager(Uint32 maxSize)
	:m_positionPool(maxSize, sizeof(PositionComponent))
	, m_physicsPool(maxSize, sizeof(PhysicsComponent))
	, m_steeringPool(maxSize, sizeof(SteeringComponent))
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
	//call destructor for all COMPONENT_MANAGER
	for (auto& it : m_positionCOMPONENT_MANAGER)
	{
		PositionComponent* pComponent = it.second;
		pComponent->~PositionComponent();
	}
	for (auto& it : m_physicsCOMPONENT_MANAGER)
	{
		PhysicsComponent* pComponent = it.second;
		pComponent->~PhysicsComponent();
	}
	for (auto& it : m_steeringCOMPONENT_MANAGER)
	{
		SteeringComponent* pComponent = it.second;
		pComponent->~SteeringComponent();
	}

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
	auto it = m_positionCOMPONENT_MANAGER.find(id);
	if (it != m_positionCOMPONENT_MANAGER.end())
	{
		return it->second;
	}
	else
	{
		return NULL;
	}
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
		m_positionCOMPONENT_MANAGER[newID] = pComponent;
		ms_nextPositionComponentID++;//increment id
	}

	return newID;
}

void ComponentManager::deallocatePositionComponent(const ComponentID& id)
{
	auto it = m_positionCOMPONENT_MANAGER.find(id);

	if (it != m_positionCOMPONENT_MANAGER.end())//found it
	{
		PositionComponent* ptr = it->second;
		m_positionCOMPONENT_MANAGER.erase(it);

		ptr->~PositionComponent();
		m_positionPool.freeObject((Byte*)ptr);
	}
}


PhysicsComponent* ComponentManager::getPhysicsComponent(const ComponentID& id)
{
	auto it = m_physicsCOMPONENT_MANAGER.find(id);
	if (it != m_physicsCOMPONENT_MANAGER.end())
	{
		return it->second;
	}
	else
	{
		return NULL;
	}

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
		m_physicsCOMPONENT_MANAGER[newID] = pComponent;
		ms_nextPhysicsComponentID++;//increment id
	}

	return newID;
}

void ComponentManager::deallocatePhysicsComponent(const ComponentID& id)
{
	auto it = m_physicsCOMPONENT_MANAGER.find(id);

	if (it != m_physicsCOMPONENT_MANAGER.end())//found it
	{
		PhysicsComponent* ptr = it->second;
		m_physicsCOMPONENT_MANAGER.erase(it);

		//hold for later
		Byte* pByte = (Byte*)ptr;

		ptr->~PhysicsComponent();
		m_physicsPool.freeObject(pByte);
	}
}


SteeringComponent* ComponentManager::getSteeringComponent(const ComponentID& id)
{
	auto it = m_steeringCOMPONENT_MANAGER.find(id);
	if (it != m_steeringCOMPONENT_MANAGER.end())
	{
		return it->second;
	}
	else
	{
		return NULL;
	}

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
		m_steeringCOMPONENT_MANAGER[newID] = pComponent;
		ms_nextSteeringComponentID++;//increment id
	}

	return newID;
}

void ComponentManager::deallocateSteeringComponent(const ComponentID& id)
{
	auto it = m_steeringCOMPONENT_MANAGER.find(id);

	if (it != m_steeringCOMPONENT_MANAGER.end())//found it
	{
		SteeringComponent* ptr = it->second;
		m_steeringCOMPONENT_MANAGER.erase(it);

		//hold for later
		Byte* pByte = (Byte*)ptr;

		ptr->~SteeringComponent();
		m_steeringPool.freeObject(pByte);
	}
}


const float ELAPSED_TIME_PHYSICS_MULT = 1.0f;

void ComponentManager::update(float elapsedTime)
{
	updateSteering(elapsedTime*ELAPSED_TIME_PHYSICS_MULT);
	updatePhysics(elapsedTime*ELAPSED_TIME_PHYSICS_MULT);
}

void ComponentManager::updatePhysics(float elapsedTime)
{
	for (auto& it : m_physicsCOMPONENT_MANAGER)
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
	for (auto& it : m_steeringCOMPONENT_MANAGER)
	{
		SteeringComponent* pSteering = it.second;
		assert(pSteering != NULL);
		PhysicsComponent* pPhysics = getPhysicsComponent(pSteering->getID());
		assert(pPhysics != NULL);
		pSteering->applySteering(*pPhysics);
	}

}