#include "SeparationSteering.h"
#include "UnitManager.h"

SeparationSteering::SeparationSteering(
	const UnitID& unitID, 
	float radius) : Steering(SEPARATION)
{
	setOwnerID(unitID);
	m_radius = radius;
}

Steering* SeparationSteering::getSteering()
{
	// Get owner
	Unit* p_owner = UNITS->getUnit(m_ownerID);

	// Create the structure to hold our output
	PhysicsData data = p_owner->getPhysicsComponent()->getData();

	// Get owner position
	Vector2 ownerPos = p_owner->getPosition();

	// Get units within radius
	std::vector<Unit*> unitList = UNITS->findUnitsInRadius(ownerPos, m_radius);

	// Move away from each nearby unit
	for (auto& u : unitList)
	{
		// Skip if self
		if (u == p_owner)
		{
			continue;
		}

		Vector2 offset = (ownerPos - u->getPosition());
		float dist = (p_owner->getMaxAcc() * (m_radius - offset.magnitude()) / m_radius);		
		data.acc += offset.normalized() * dist;
	}

	// Output steering
	this->m_data = data;
	return this;
}