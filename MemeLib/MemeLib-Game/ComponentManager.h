#ifndef _COMPONENT_MANAGER_H_
#define _COMPONENT_MANAGER_H_

#include <map>
#include <Trackable.h>
#include <MemoryPool.h>
#include "Component.h"
#include "TransformCOmponent.h"
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
	void	cleanup();

	TransformComponent*	getTransformComponent(const ComponentID& id);
	ComponentID			allocateTransformComponent(const TransformData& data = ZERO_POSITION_DATA, bool shouldWrap = true);
	void				deallocateTransformComponent(const ComponentID& id);

	PhysicsComponent*	getPhysicsComponent(const ComponentID& id);
	ComponentID			allocatePhysicsComponent(const ComponentID& positionComponentID, const PhysicsData& data = ZERO_PHYSICS_DATA);
	void				deallocatePhysicsComponent(const ComponentID& id);

	SteeringComponent*	getSteeringComponent(const ComponentID& id);
	ComponentID			allocateSteeringComponent(const ComponentID& physicsComponentID, const SteeringData& data = ZERO_STEERING_DATA);
	void				deallocateSteeringComponent(const ComponentID& id);

	void update(float elapsedTime);

private:
	ComponentManager(Uint32 maxSize);
	~ComponentManager();

	std::map<ComponentID, TransformComponent*> m_positionCOMPONENT_MANAGER;
	MemoryPool m_positionPool;

	std::map<ComponentID, PhysicsComponent*> m_physicsCOMPONENT_MANAGER;
	MemoryPool m_physicsPool;

	std::map<ComponentID, SteeringComponent*> m_steeringCOMPONENT_MANAGER;
	MemoryPool m_steeringPool;

	static ComponentID ms_nextPositionComponentID;
	static ComponentID ms_nextPhysicsComponentID;
	static ComponentID ms_nextSteeringComponentID;

	void updatePhysics(float elapsedTime);
	void updateSteering(float elapsedTime);

	static ComponentManager* sp_instance;
};

#endif