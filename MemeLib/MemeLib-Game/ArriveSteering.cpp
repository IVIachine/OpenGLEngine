#include "ArriveSteering.h"
#include "Steering.h"
#include "Game.h"
#include "UnitManager.h"
#include "Unit.h"

ArriveSteering::ArriveSteering(const UnitID& ownerID, const Vec3& targetLoc, const UnitID& targetID, float theRadius, float theSlowRadius, double arriveTime)
{
	setOwnerID(ownerID);
	setTargetID(targetID);
	setTargetLoc(targetLoc);
	mRadius = theRadius;
	mSlowRadius = theSlowRadius;
	mTimeToTarget = .1;
}
Steering* ArriveSteering::getSteering()
{
	Vec3 diff;

	Unit* pOwner = UNITS->getUnit(mOwnerID);
	//are we seeking a location or a unit?
	if (mTargetID != INVALID_UNIT_ID)
	{
		//seeking unit
		Unit* pTarget = UNITS->getUnit(mTargetID);
		assert(pTarget != NULL);
		mTargetLoc = pTarget->getPositionComponent()->getPosition();
	}

	PhysicsData data = pOwner->getPhysicsComponent()->getData();
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
		targetSpeed = pOwner->getMaxSpeed();
	}
	else
	{
		targetSpeed = pOwner->getMaxSpeed() * distance / mSlowRadius;
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
