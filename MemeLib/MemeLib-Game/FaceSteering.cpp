#include "FaceSteering.h"
#include "Steering.h"
#include "Game.h"
#include "UnitManager.h"
#include "Unit.h"
#include <math.h>
#include <cmath>

const double M_PI = 3.1415926535897932384626433832795028841971693993751058209749445923078164062862089986280348;

FaceSteering::FaceSteering(const UnitID& ownerID, const Vec3& targetLoc, const UnitID& targetID, float theRadius, float theSlowRadius)
{
	setOwnerID(ownerID);
	setTargetID(targetID);
	setTargetLoc(targetLoc);
	mTargetRadius = theRadius;
	mSlowRadius = theSlowRadius;
	mTimeToTarget = .1;
}


Steering* FaceSteering::getSteering()
{
	float rotation;
	float mTargetSteer = 0;
	Unit* pOwner = UNITS->getUnit(mOwnerID);
	if (mTargetID != INVALID_UNIT_ID)
	{
		//seeking unit
		Unit* pTarget = UNITS->getUnit(mTargetID);
		assert(pTarget != NULL);

		mTargetLoc = pTarget->getPositionComponent()->getPosition();
	}

	PhysicsData data = pOwner->getPhysicsComponent()->getData();
	Vec3 direction2 = mTargetLoc - pOwner->getPositionComponent()->getPosition();

	if (glm::length(direction2) == 0)
	{
		return nullptr;
	}

	float orientation = atan2(-direction2.x, direction2.z);
	rotation = orientation - pOwner->getPositionComponent()->getFacing();

	//Cite: jdhaan, http://stackoverflow.com/questions/4633177/c-how-to-wrap-a-float-to-the-interval-pi-pi

	if (rotation>0.f)
		rotation = fmod(rotation + M_PI, 2.0f*M_PI) - M_PI;
	else
		rotation = fmod(rotation - M_PI, 2.0f*M_PI) + M_PI;

	float rotationSize = abs(rotation);

	if (rotationSize < mTargetRadius)
	{
		return nullptr;
	}

	float targetRotation;

	if (rotationSize > mSlowRadius)
	{
		targetRotation = pOwner->getMaxRotVel();
	}
	else
	{
		targetRotation = pOwner->getMaxRotVel() * rotationSize / mSlowRadius;
	}

	targetRotation = targetRotation * (rotation / rotationSize);

	float temp = targetRotation - data.rotVel;
	temp = temp / mTimeToTarget;


	float anglAcl = abs(temp);
	if (anglAcl > data.maxRotAcc)
	{
		temp = temp / anglAcl;
		temp = temp * data.maxRotAcc;
	}

	data.rotAcc = temp;
	pOwner->getPhysicsComponent()->setData(data);
	this->setData(data);
	return this;
}

