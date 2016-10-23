#include "WanderSteering.h"
#include "Steering.h"
#include "Game.h"
#include "UnitManager.h"
#include "Unit.h"


WanderSteering::WanderSteering(
	const UnitID& ownerID,
	const Vector2& targetPos,
	float arriveRadius,
	float arriveSlowRadius,
	float arriveTime,
	float faceRadius,
	float faceSlowRadius,
	float faceTime) : Steering(WANDER)
{
	mp_steering = new ArriveAndFaceSteering(
		ownerID, 
		targetPos, 
		INVALID_UNIT_ID,
		arriveRadius, 
		arriveSlowRadius,
		arriveTime,
		faceSlowRadius);

	setOwnerID(ownerID);
	setTargetID(INVALID_UNIT_ID);
	setTargetPos(targetPos);
}

WanderSteering::~WanderSteering()
{
	delete mp_steering;
	mp_steering = NULL;
}


Steering* WanderSteering::getSteering()
{
	Unit* p_owner = UNITS->getUnit(m_ownerID);
	Vector2 position = p_owner->getTransformComponent()->getPosition();

	if (!m_isWandering)
	{
		float random = genRandomFloat();
		if (random < m_wanderRate)
		{
			setTargetPos(position + genWanderPos());
			m_isWandering = true;
		}
	}
	else
	{
		if (Vector2::distance(position, m_targetPos) < m_wanderOffset)
		{
			m_isWandering = false;
		}
	}

	if (mp_steering->getSteering() != NULL)
	{
		this->m_data = mp_steering->getData();
	}

	return this;
}

Vector2 WanderSteering::genWanderPos()
{
	float len = genRandomFloat(0.0f, m_wanderRadius);
	float dir = (float)(-180 + (rand() % 180)) * Maths::DEG_TO_RAD;

	return Vector2::lengthDir(len, dir);
}