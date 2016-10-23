#include "Message_UpdateFlocking.h"
#include "UnitManager.h"
#include "ComponentManager.h"
#include "GameController.h"
#include "FlockSteering.h"

Message_UpdateFlocking::Message_UpdateFlocking(
	float aRadius,
	float cRadius,
	float sRadius,
	float aWeight,
	float cWeight,
	float sWeight) : GameMessage(MSG_UPDATE_FLOCKING)
{
	m_aRadius = aRadius;
	m_cRadius = cRadius;
	m_sRadius = sRadius;

	m_aWeight = aWeight;
	m_cWeight = cWeight;
	m_sWeight = sWeight;
}

Message_UpdateFlocking::~Message_UpdateFlocking()
{
}


void Message_UpdateFlocking::process()
{
	for (auto& u : UNITS->toList())
	{
		SteeringComponent* p_component = u->getSteeringComponent();		
		Steering* p_steering = p_component->getSteering();
		FlockSteering* p_flock = static_cast<FlockSteering*>(p_component->getSteering());

		if (p_flock != NULL)
		{
			p_flock->setValues(
				m_aRadius,
				m_cRadius,
				m_sRadius,
				m_aWeight,
				m_cWeight,
				m_sWeight);
		}
	}
}