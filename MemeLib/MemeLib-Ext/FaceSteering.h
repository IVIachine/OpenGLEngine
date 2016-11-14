#pragma once
#include "Steering.h"
class FaceSteering :public Steering
{
private:
	float mTimeToTarget;
	float mTargetRadius, mSlowRadius;
public:
	FaceSteering(const GameObjectID& ownerID, const Vec3& targetLoc, const GameObjectID& targetID, float theRadius, float theSlowRadius);
	Steering* getSteering();
};

