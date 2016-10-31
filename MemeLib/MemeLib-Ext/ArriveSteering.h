#ifndef _ARRIVE_STEERING_H_
#define _ARRIVE_STEERING_H_

#include "Steering.h"
class ArriveSteering :public Steering
{
private:
	float mRadius;
	float mSlowRadius;
	float mTimeToTarget;
public:
	ArriveSteering(const UnitID& ownerID, const Vec3& targetLoc, const UnitID& targetID, float theRadius, float theSlowRadius, float arriveTime);
	virtual Steering* getSteering();
};

#endif