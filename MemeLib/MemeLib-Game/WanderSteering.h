#ifndef _WANDER_STEERING_H_
#define _WANDER_STEERING_H_

#include <Trackable.h>
#include "Steering.h"
#include "ArriveAndFaceSteering.h"

class WanderSteering : public Steering
{
public:
	WanderSteering(
		const UnitID& ownerID,
		const Vector2& destination,
		float arriveRadius = 0.15f,
		float arriveSlowRadius = 150.0f,
		float arriveTime = 0.1f,
		float faceRadius = 1.0f,
		float faceSlowRadius = 0.5f,
		float faceTime = 0.1f);
	~WanderSteering();

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

};

#endif