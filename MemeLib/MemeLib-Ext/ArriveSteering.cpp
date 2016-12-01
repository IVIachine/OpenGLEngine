#include "ArriveSteering.h"
#include "Steering.h"
#include "Game.h"
#include "UnitManager.h"
#include "Unit.h"

ArriveSteering::ArriveSteering(const GameObjectID& ownerID, const Vec3& targetLoc, const GameObjectID& targetID, float theRadius, float theSlowRadius, float arriveTime)
{
	setOwnerID(ownerID);
	setTargetID(targetID);
	setTargetLoc(targetLoc);
	mRadius = theRadius;
	mSlowRadius = theSlowRadius;
	mTimeToTarget = 0.1f;
}
Steering* ArriveSteering::getSteering()
{
	Vec3 diff;

	Unit* pOwner = UNITS->getUnit(mOwnerID);
	PhysicsData data = pOwner->getPhysicsComponent()->getData();

	//are we seeking a location or a unit?
	if (mTargetID != INVALID_GOBJ_ID)
	{
		//seeking unit
		Unit* pTarget = UNITS->getUnit(mTargetID);
		assert(pTarget != NULL);
		mTargetLoc = pTarget->getPositionComponent()->getPosition();
	}

	diff = mTargetLoc - pOwner->getPositionComponent()->getPosition();
	float distance = glm::length(diff);

	if (distance < mRadius)
	{
		return nullptr;
	}

	float targetSpeed;
	Vec3 targetVelocity;

	if (distance > mSlowRadius)
	{
		targetSpeed = data.maxSpeed;
	}
	else
	{
		targetSpeed = data.maxSpeed * distance / mSlowRadius;
	}

	targetVelocity = diff;
	glm::normalize(targetVelocity);
	targetVelocity *= targetSpeed;

	diff = targetVelocity - data.vel;
	diff /= mTimeToTarget;


	if (glm::length(diff) > pOwner->getMaxAcc())
	{
		glm::normalize(diff);
		diff *= pOwner->getMaxAcc();
	}
	data.acc = diff;
	pOwner->getPhysicsComponent()->setData(data);
	this->setData(data);
	return this;
}
