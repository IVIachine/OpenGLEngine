#pragma once
#include "Steering.h"
class ArriveSteering :public Steering
{
private:
	float mRadius;
	float mSlowRadius;
	double mTimeToTarget;
public:
	ArriveSteering(const UnitID& ownerID, const Vec3& targetLoc, const UnitID& targetID, float theRadius, float theSlowRadius, double arriveTime);
	virtual Steering* getSteering();
};

