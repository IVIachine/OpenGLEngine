#ifndef _ARRIVE_STEERING_H_
#define _ARRIVE_STEERING_H_

#include <Trackable.h>
#include "Steering.h"

class ArriveSteering : public Steering
{
public:
	ArriveSteering(
		const UnitID& ownerID,
		const Vector2& targetPos,
		const UnitID& targetID = INVALID_UNIT_ID,
		float radius = 5.0f,
		float slowRadius = 150.0f,
		float timeToTarget = 0.1f);

	virtual Steering* getSteering();

private:
	float m_targetRadius;
	float m_slowRadius;
	float m_timeToTarget;
};

#endif