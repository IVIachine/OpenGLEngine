#include "ArriveSteering.h"
#include "Steering.h"
#include "Game.h"
#include "UnitManager.h"
#include "Unit.h"


ArriveSteering::ArriveSteering(
	const UnitID& ownerID, 
	const Vector2& targetPos,
	const UnitID& targetID,
	float radius,
	float slowRadius,
	float timeToTarget) : Steering(ARRIVE)
{
	m_targetRadius = radius;
	m_slowRadius = slowRadius;
	m_timeToTarget = timeToTarget;

	setOwnerID(ownerID);
	setTargetID(targetID);
	setTargetPos(targetPos);
}

Steering* ArriveSteering::getSteering()
{
	// Get owner
	Unit* p_owner = UNITS->getUnit(m_ownerID);

	// Are we seeking a location or a unit?
	if (m_targetID != INVALID_UNIT_ID)
	{
		// Seeking unit
		Unit* p_target = UNITS->getUnit(m_targetID);
		assert(p_target != NULL);
		m_targetPos = p_target->getTransformComponent()->getPosition();
	}

	// Get physics data
	PhysicsData data = p_owner->getPhysicsComponent()->getData();

	// Get the direction to the target
	Vector2 position = p_owner->getTransformComponent()->getPosition();
	Vector2 direction = (m_targetPos - position);
	float distance = direction.magnitude();

	// Check if we are there, return no steering
	if (distance < m_targetRadius)
	{
		data.vel = Vector2::ZERO;
		data.acc = Vector2::ZERO;
		p_owner->getPhysicsComponent()->setData(data);
		this->m_data = data;
		return this;
	}

	float targetSpeed = 0.0f;
	// If we are outside the slowRadius, then go max speed
	if (distance > m_slowRadius)
	{
		targetSpeed = p_owner->getMaxSpeed();
	}
	// Otherwise calculate a scaled speed
	else
	{
		targetSpeed = p_owner->getMaxSpeed() * distance / m_slowRadius;
	}

	// The target velocity combines speed and direction
	Vector2 targetVelocity = direction.normalized() * targetSpeed;

	// Acceleration tries to get to the target velocity
	data.acc = targetVelocity - data.vel;
	data.acc /= m_timeToTarget;

	// Check if the acceleration is too fast
	if (data.acc.magnitude() > p_owner->getMaxAcc())
	{
		data.acc.normalize();
		data.acc *= p_owner->getMaxAcc();
	}

	// Output the steering
	p_owner->getPhysicsComponent()->setData(data);
	this->m_data = data;
	return this;
}