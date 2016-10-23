#include "WanderAndChaseSteering.h"
#include "Steering.h"
#include "Game.h"
#include "UnitManager.h"
#include "Unit.h"
//#include "Gizmos.h"

WanderAndChaseSteering::WanderAndChaseSteering(
	const UnitID& ownerID,
	const Vector2& targetPos,
	const UnitID& targetID,
	float arriveRadius,
	float arriveSlowRadius,
	float arriveTime,
	float faceRadius,
	float faceSlowRadius,
	float faceTime,
	float wanderOffset,
	float wanderRadius,
	float wanderRate) : Steering(WANDER_AND_CHASE)
{
	mp_steering = new ArriveAndFaceSteering(
		ownerID,
		targetPos,
		INVALID_UNIT_ID,
		arriveRadius,
		arriveSlowRadius,
		arriveTime,
		faceSlowRadius);

	m_wanderOffset = wanderOffset;
	m_wanderRadius = wanderRadius;
	m_wanderRate = wanderRate;

	setOwnerID(ownerID);
	setTargetID(targetID);
	setTargetPos(targetPos);
}

WanderAndChaseSteering::~WanderAndChaseSteering()
{
	delete mp_steering;
	mp_steering = NULL;
}

Steering* WanderAndChaseSteering::getSteering()
{
	Unit* p_owner = UNITS->getUnit(m_ownerID);
	Vector2 position = p_owner->getTransformComponent()->getPosition();

	if (m_targetID != INVALID_UNIT_ID)
	{
		Unit* p_target = UNITS->getUnit(m_targetID);
		assert(p_target != NULL);

		Vector2 targetPos = p_target->getTransformComponent()->getPosition();
		float distance = Vector2::distance(position, targetPos);

		if (distance < m_wanderRadius)
		{
			setTargetPos(targetPos);
		}
		else
		{
			wander();
		}
	}
	else
	{
		wander();
	}

	if (mp_steering->getSteering() != NULL)
	{
		this->m_data = mp_steering->getData();
	}

	return this;
}

Vector2 WanderAndChaseSteering::genWanderPos()
{
	float len = genRandomFloat(0.0f, m_wanderRadius);
	float dir = (float)(-180 + (rand() % 360)) * Maths::DEG_TO_RAD;
	return Vector2::lengthDir(len, dir);
}

void WanderAndChaseSteering::wander()
{
	Vector2 position = UNITS->getUnit(m_ownerID)->getTransformComponent()->getPosition();

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
}