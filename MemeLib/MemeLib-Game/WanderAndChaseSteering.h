#ifndef _WANDER_AND_CHASE_STEERING_H_
#define _WANDER_AND_CHASE_STEERING_H_

#include <Trackable.h>
#include "Steering.h"
#include "ArriveAndFaceSteering.h"

class WanderAndChaseSteering : public Steering
{
public:
	WanderAndChaseSteering(
		const UnitID& ownerID,
		const Vector2& destination,
		const UnitID& targetID = INVALID_UNIT_ID,
		float arriveRadius = 0.15f,
		float arriveSlowRadius = 150.0f,
		float arriveTime = 0.1f,
		float faceRadius = 1.0f,
		float faceSlowRadius = 0.5f,
		float faceTime = 0.1f,
		float wanderOffset = 0.1f,
		float wanderRadius = 64.0f,
		float wanderRate = 0.25f);
	~WanderAndChaseSteering();

	virtual Steering* getSteering();

	void setTargetPos(const Vector2& pos)
	{
		Steering::setTargetPos(pos);
		mp_steering->setTargetPos(pos);
	}

private:
	ArriveAndFaceSteering* mp_steering;
	bool m_isWandering = false;
	float m_wanderOffset = 0.1f;
	float m_wanderRadius = 64;
	float m_wanderRate = 0.25f;

	Vector2 genWanderPos();
	void wander();

};

#endif