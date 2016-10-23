#include "FaceSteering.h"
#include "Steering.h"
#include "Game.h"
#include "UnitManager.h"
#include "Unit.h"
#include "Maths.h"

FaceSteering::FaceSteering(
	const UnitID& ownerID, 
	const Vector2& targetPos, 
	const UnitID& targetID,
	float slowRadius,
	float timeToTarget) : Steering(FACE)
{
	setOwnerID(ownerID);
	setTargetPos(targetPos);
	setTargetID(targetID);

	m_slowRadius = slowRadius * Maths::DEG_TO_RAD;
	m_timeToTarget = timeToTarget;
}

Steering* FaceSteering::getSteering()
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

	// Create the structure to hold our output
	PhysicsData data = p_owner->getPhysicsComponent()->getData();

	// Get the native direction to the target
	Vector2 position = p_owner->getTransformComponent()->getPosition();
	Vector2 direction = m_targetPos - position;

	// Check if we are there, return no steering
	if (direction == Vector2::ZERO)
	{
		return NULL;
	}

	float angle = Vector2::angle(position, m_targetPos);
	float rotation = (angle - p_owner->getRotation());

	// Map the result to the (-pi, pi) interval
	rotation = Maths::mapToRange(rotation, -Maths::PI, Maths::PI);
	float rotationSize = abs(rotation);

	float targetRotation = 0.0f;
	// If we are outside the slowRadius, then go use maximum rotation
	if (rotationSize > m_slowRadius)
	{
		targetRotation = p_owner->getMaxRotAcc();
	}
	// Otherwise calculate a scaled speed
	else
	{
		targetRotation = p_owner->getMaxRotAcc() * rotationSize / m_slowRadius;
	}

	// The final target rotation combines
	// speed (already in the variable) and direction
	targetRotation *= rotation / rotationSize;

	// Acceleration tries to get to the target velocity
	data.rotAcc = (targetRotation - data.rotVel);
	data.rotAcc /= m_timeToTarget;

	// Check if the acceleration is too great
	float angularAcceleration = abs(data.rotAcc);
	if (angularAcceleration > p_owner->getMaxRotAcc())
	{
		data.rotAcc /= angularAcceleration;
		data.rotAcc *= p_owner->getMaxRotAcc();
	}

	// Output the steering
	p_owner->getPhysicsComponent()->setData(data);
	this->m_data = data;
	return this;
}