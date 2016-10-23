#include "CohesionSteering.h"
#include "UnitManager.h"

CohesionSteering::CohesionSteering(
	const UnitID& ownerID, 
	float startRadius) : Steering(COHESION)
{
	setOwnerID(ownerID);
	m_radius = startRadius;
}
Steering* CohesionSteering::getSteering()
{
	// Get owner
	Unit* p_owner = UNITS->getUnit(m_ownerID);

	// Create the structure to hold our output
	PhysicsData data = p_owner->getPhysicsComponent()->getData();

	// Get units within radius
	std::vector<Unit*> unitList = UNITS->findUnitsInRadius(p_owner->getPosition(), m_radius);

	// Calculate percieved center of nearby units
	Vector2 center = Vector2::ZERO;
	for (auto& u : unitList)
	{
		center += u->getPosition();
	}
	center /= (float)unitList.size();
	
	// Move towards center
	Vector2 dir = center - p_owner->getPosition();
	dir = dir.normalized() * p_owner->getMaxAcc();
	data.acc = dir;

	// Output steering
	this->m_data = data;
	return this;
}