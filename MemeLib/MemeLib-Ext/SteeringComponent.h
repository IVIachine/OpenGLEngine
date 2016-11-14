#ifndef _STEERING_COMPONENT_H_
#define _STEERING_COMPONENT_H_

#include <Trackable.h>
#include "Vector3.h"
#include "Component.h"
#include "Unit.h"

class PhysicsComponent;
class Steering;
enum Steering::SteeringType;

struct SteeringData : public Trackable
{
	SteeringData() :type(Steering::INVALID_TYPE), targetLoc(Vec3(0, 0, 0)), ownerID(INVALID_GOBJ_ID), targetID(INVALID_GOBJ_ID) {};
	SteeringData(Steering::SteeringType theType, const Vec3& theTargetLoc = Vec3(0, 0, 0), GameObjectID theOwner = INVALID_GOBJ_ID, GameObjectID theTarget = INVALID_GOBJ_ID)
		:type(theType), targetLoc(theTargetLoc), ownerID(theOwner), targetID(theTarget) {};
	Steering::SteeringType type;
	Vec3 targetLoc;
	GameObjectID ownerID;
	GameObjectID targetID;
};

const SteeringData ZERO_STEERING_DATA;

class SteeringComponent :public Component
{
public:
	SteeringComponent(const ComponentID& id, const ComponentID& physicsComponentID);
	~SteeringComponent();

	//getters and setters
	Steering::SteeringType getType() const { return mData.type; };
	const Vec3& getTargetLoc() const { return mData.targetLoc; };
	GameObjectID getOwnerID() const { return mData.ownerID; };
	GameObjectID getTargetID() const { return mData.targetID; };
	ComponentID getPhysicsComponentID() const { return mPhysicsComponentID; };
	const SteeringData& getData() const { return mData; };
	void setData(const SteeringData& data, Path path = Path());
	void setTargetLoc(const Vec3& pos) { mData.targetLoc = pos; };
	void setTargetUnitID(const GameObjectID& id) { mData.targetID = id; };
	void applySteering(PhysicsComponent& physicsComponent);
private:
	ComponentID mPhysicsComponentID;
	SteeringData mData;
	Steering* mpSteering;

	friend class ComponentManager;
};

#endif // !_STEERING_COMPONENT_H_
