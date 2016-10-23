#ifndef _FACE_STEERING_H_
#define _FACE_STEERING_H_

#include <Trackable.h>
#include "Steering.h"

class FaceSteering : public Steering
{
public:
	FaceSteering(
		const UnitID& ownerID,
		const Vector2& targetPos,
		const UnitID& targetID = INVALID_UNIT_ID,
		float slowRadius = 50.0f,
		float timeToTarget = 0.001f);

	Steering* getSteering() override;

private:
	float m_slowRadius;
	float m_timeToTarget;
};

#endif
