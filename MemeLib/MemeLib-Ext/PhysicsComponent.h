#ifndef _PHYSICS_COMPONENT_H_
#define _PHYSICS_COMPONENT_H_

#include "Component.h"
#include "PhysicsData.h"
#include <cfloat>

class PositionComponent;

class PhysicsComponent :public Component
{
public:
	PhysicsComponent(const ComponentID& id, const ComponentID& posID) : Component(id), mPositionComponentID(posID) {};
	~PhysicsComponent() {};

	void setData(const PhysicsData& data) { mData = data; };
	void modData(const PhysicsData& data);
	const PhysicsData& getData() const { return mData; };
	const Vec3& getVelocity() const { return mData.vel; };
	const Vec3& getAcceleration() const { return mData.acc; };
	float getRotationalVelocity() const { return mData.rotVel; };
	float getRotationalAcceleration() const { return mData.rotAcc; };

private:
	PhysicsData mData;
	ComponentID mPositionComponentID;

	void integrate(PositionComponent& posComponent, float elapsedTime);

	friend class ComponentManager;
};

#endif // !_PHYSICS_COMPONENT_H_