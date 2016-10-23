#include "AlignmentSteering.h"
#include "UnitManager.h"

AlignmentSteering::AlignmentSteering(
	const UnitID& ownerID, 
	float radius) : Steering(ALIGNMENT)
{
	setOwnerID(ownerID);
	m_radius = radius;
}

Steering* AlignmentSteering::getSteering()
{
	// Get Owner
	Unit* p_owner = UNITS->getUnit(m_ownerID);
	
	// Create the structure to hold our output
	PhysicsData data = p_owner->getPhysicsComponent()->getData();

	// Get units within radius
	std::vector<Unit*> unitList = UNITS->findUnitsInRadius(p_owner->getPosition(), m_radius);

	// Get the average rotation of nearby units
	float rotation = 0.0f;
	for (auto& u : unitList)
	{
		rotation += u->getRotation();
	}
	rotation /= (float)unitList.size();

	// Move in facing direction
	Vector2 dir = Vector2::angle(rotation).normalized();	
	dir *= p_owner->getMaxAcc();
	data.acc = dir;

	// Output Steering
	this->m_data = data;
	return this;
}