#pragma once

#include "Component.h"
#include "Vector3.h"
#include <Trackable.h>
#include <cfloat>

class PositionComponent;

static const float MAX_ACC = .5f;
static const float MAX_SPEED = .4f;
static const float MAX_ROT_ACC = 4.0f;
static const float MAX_ROT_VEL = 8.0f;

struct PhysicsData : public Trackable
{
	PhysicsData(
		const Vec3& theVel
		, const Vec3& theAcc
		, float theRotVel
		, float theRotAcc
		, float theMaxSpeed = MAX_SPEED
		, float theMaxAcc = MAX_ACC
		, float theMaxRotVel = MAX_ROT_VEL
		, float theMaxRotAcc = MAX_ROT_ACC)
		:vel(theVel)
		, acc(theAcc)
		, rotVel(theRotVel)
		, rotAcc(theRotAcc)
		, maxSpeed(theMaxSpeed)
		, maxAccMagnitude(theMaxAcc)
		, maxRotVel(theMaxRotVel)
		, maxRotAcc(theRotAcc)
	{};

	PhysicsData()
		:vel(Vec3(0,0,0))
		, acc(Vec3(0, 0, 0))
		, rotVel(0.0f)
		, rotAcc(0.0f)
		, maxSpeed(MAX_SPEED)
		, maxAccMagnitude(MAX_ACC)
		, maxRotVel(MAX_ROT_VEL)
		, maxRotAcc(MAX_ROT_ACC)
	{};

	Vec3 vel;
	Vec3 acc;
	float rotVel;
	float rotAcc;
	float maxSpeed;
	float maxAccMagnitude;
	float maxRotVel;
	float maxRotAcc;
};

const PhysicsData ZERO_PHYSICS_DATA;

class PhysicsComponent :public Component
{
public:

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

	PhysicsComponent(const ComponentID& id, const ComponentID& posID) :Component(id), mPositionComponentID(posID) {};
	~PhysicsComponent() {};

	void integrate(PositionComponent& posComponent, float elapsedTime);

	friend class ComponentManager;
};