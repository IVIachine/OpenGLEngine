#ifndef _PHYSICS_DATA_H_
#define _PHYSICS_DATA_H_

#include <Trackable.h>
#include <Vector3.h>

static const float MAX_ACC = 2.0f;
static const float MAX_SPEED = 0.65f;
static const float MAX_ROT_ACC = 150.0f;
static const float MAX_ROT_VEL = 200.0f;

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
		:vel(Vec3(0, 0, 0))
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

#endif // !_PHYSICS_DATA_H_
