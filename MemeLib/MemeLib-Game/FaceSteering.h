#pragma once
#include "Steering.h"
class FaceSteering :public Steering
{
private:
	double mTimeToTarget;
	float mTargetRadius, mSlowRadius;
public:
	FaceSteering(const UnitID& ownerID, const Vec3& targetLoc, const UnitID& targetID, float theRadius, float theSlowRadius);
	Steering* getSteering();
};

