#ifndef _COMPONENT_MANAGER_H_
#define _COMPONENT_MANAGER_H_

#include <Dictionary.h>
#include <MemoryPool.h>
#include "Component.h"
#include "PositionComponent.h"
#include "PhysicsComponent.h"
#include "SteeringComponent.h"

#define COMPONENTS ComponentManager::getInstance()

class ComponentManager : public Trackable
{
public:
	static ComponentManager*	getInstance();
	static void					disposeInstance();
	static ComponentManager*	createInstance(Uint32 maxSize);

	bool	setup();
	void	clear();

	PositionComponent*	getPositionComponent(const ComponentID& id);
	ComponentID			allocatePositionComponent(const PositionData& data = ZERO_POSITION_DATA, bool shouldWrap = true);
	bool				deallocatePositionComponent(const ComponentID& id);

	PhysicsComponent*	getPhysicsComponent(const ComponentID& id);
	ComponentID			allocatePhysicsComponent(const ComponentID& positionComponentID, const PhysicsData& data = ZERO_PHYSICS_DATA);
	bool				deallocatePhysicsComponent(const ComponentID& id);

	SteeringComponent*	getSteeringComponent(const ComponentID& id);
	ComponentID			allocateSteeringComponent(const ComponentID& physicsComponentID, const SteeringData& data = ZERO_STEERING_DATA);
	bool				deallocateSteeringComponent(const ComponentID& id);

	void update(float elapsedTime);

private:
	ComponentManager(Uint32 maxSize);
	~ComponentManager();

	Dictionary<ComponentID, PositionComponent> m_positionCOMPONENT_MANAGER;
	MemoryPool m_positionPool;

	Dictionary<ComponentID, PhysicsComponent> m_physicsCOMPONENT_MANAGER;
	MemoryPool m_physicsPool;

	Dictionary<ComponentID, SteeringComponent> m_steeringCOMPONENT_MANAGER;
	MemoryPool m_steeringPool;

	static ComponentID ms_nextPositionComponentID;
	static ComponentID ms_nextPhysicsComponentID;
	static ComponentID ms_nextSteeringComponentID;

	void updatePhysics(float elapsedTime);
	void updateSteering(float elapsedTime);

	static ComponentManager* sp_instance;
};

#endif