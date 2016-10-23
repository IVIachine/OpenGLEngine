#include "Steering.h"
#include "SeekSteering.h"
#include "Game.h"
#include "UnitManager.h"
#include "Unit.h"


SeekSteering::SeekSteering(
	const UnitID& ownerID, 
	const Vector2& targetLoc, 
	const UnitID& targetID, 
	bool shouldFlee) : Steering(shouldFlee ? Steering::FLEE : Steering::SEEK)
{
	setOwnerID(ownerID);
	setTargetID(targetID);
	setTargetPos(targetLoc);
}

Steering* SeekSteering::getSteering()
{
	Vector2 dir;
	Unit* p_owner = UNITS->getUnit(m_ownerID);
	//are we seeking a location or a unit?
	
	if (m_targetID != INVALID_UNIT_ID)
	{
		//seeking unit
		Unit* p_target = UNITS->getUnit(m_targetID);
		assert(p_target != NULL);
		m_targetPos = p_target->getTransformComponent()->getPosition();
	}

	if (m_type == Steering::SEEK)
	{
		dir = m_targetPos - p_owner->getTransformComponent()->getPosition();
	}
	else
	{
		dir = p_owner->getTransformComponent()->getPosition() - m_targetPos;
	}

	dir.normalize();
	dir *= p_owner->getMaxAcc();

	PhysicsData data = p_owner->getPhysicsComponent()->getData();
	data.acc = dir;
	data.rotVel = 0.0f;
	this->m_data = data;
	return this;
}

