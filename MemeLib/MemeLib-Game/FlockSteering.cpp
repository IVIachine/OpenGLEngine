#include "FlockSteering.h"
#include "UnitManager.h"

FlockSteering::FlockSteering(
	const UnitID& ownerID,
	float aRadius,
	float cRadius,
	float sRadius,
	float aWeight,
	float cWeight,
	float sWeight)
{
	setOwnerID(ownerID);

	m_aWeight = aWeight;
	m_cWeight = cWeight;
	m_sWeight = sWeight;

	mp_align = new AlignmentSteering(ownerID, aRadius);
	mp_cohesion = new CohesionSteering(ownerID, cRadius);
	mp_separation = new SeparationSteering(ownerID, sRadius);
	mp_face = new FaceSteering(ownerID, Vector2::ZERO);
}

FlockSteering::~FlockSteering()
{
	delete mp_align;
	mp_align = NULL;

	delete mp_cohesion;
	mp_cohesion = NULL;

	delete mp_separation;
	mp_separation = NULL;

	delete mp_face;
	mp_face = NULL;
}


Steering* FlockSteering::getSteering()
{
	/*	Source
	* * * * * * * * * * * * */
	// http://www.kfish.org/boids/pseudocode.html

	// Get Owner
	Unit* owner = UNITS->getUnit(m_ownerID);

	// Create the structure to hold our output
	PhysicsData data = owner->getPhysicsComponent()->getData();
	
	// Cohesion
	// Rule 1: Boids try to fly towards the centre of mass of neighbouring boids
	PhysicsData cData = mp_cohesion->getSteering()->getData();
	data.acc += cData.acc;

	// Separation
	// Rule 2: Boids try to keep a small distance away from other objects (including other boids)
	PhysicsData sData = mp_separation->getSteering()->getData();
	data.acc += sData.acc;

	// Alignment
	// Rule 3: Boids try to match velocity with near boids
	PhysicsData aData = mp_align->getSteering()->getData();
	data.acc += aData.acc;

	// blend
	data.acc *= m_aWeight;
	data.acc *= m_cWeight;
	data.acc *= m_sWeight;
	
	// Apply linear
	data.acc = data.acc.normalized() * owner->getMaxAcc();

	// Apply angular
	mp_face->setTargetPos(owner->getPosition() + data.vel);
	data.rotAcc = mp_face->getSteering()->getData().rotAcc;

	// Output Steering
	this->m_data = data;
	return this;
}