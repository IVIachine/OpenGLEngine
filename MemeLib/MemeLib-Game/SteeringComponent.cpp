#include "ComponentManager.h"
#include "SteeringComponent.h"
#include "SeekSteering.h"
#include "FaceSteering.h"
#include "ArriveSteering.h"
#include "ArriveAndFaceSteering.h"
#include "WanderSteering.h"
#include "WanderAndChaseSteering.h"
#include "FlockSteering.h"

SteeringComponent::SteeringComponent(
	const ComponentID& id, 
	const ComponentID& physicsComponentID) : Component(id), m_physicsID(physicsComponentID), mp_steering(NULL)
{
}

SteeringComponent::~SteeringComponent()
{
	delete mp_steering;
}


void SteeringComponent::applySteering(PhysicsComponent& physicsComponent)
{
	if (mp_steering != NULL)
	{
		//allow Steering to run
		mp_steering->update();
		//set physics data to that of the Steering
		physicsComponent.setData(mp_steering->getData());
		//update component's data
		m_steeringData.targetPos = mp_steering->getTargetLoc();
	}
}

void SteeringComponent::setData(const SteeringData& data)
{
	m_steeringData = data;

	switch (data.type)
	{
		case Steering::SEEK:
		{
			setSteering(new SeekSteering(
				data.ownerID,
				data.targetPos,
				data.targetID, false));
			break;
		}
		case Steering::FLEE:
		{
			setSteering(new SeekSteering(
					data.ownerID,
					data.targetPos,
					data.targetID, true));
			break;
		}
		case Steering::ARRIVE:
		{
			setSteering(new ArriveSteering(
				data.ownerID,
				data.targetPos,
				data.targetID));
			
			break;
		}
		case Steering::FACE:
		{
			setSteering(new FaceSteering(
				data.ownerID,
				data.targetPos));

			break;
		}
		case Steering::ARRIVE_AND_FACE:
		{
			setSteering(new ArriveAndFaceSteering(
				data.ownerID,
				data.targetPos,
				data.targetID));

			break;
		}
		case Steering::WANDER:
		{
			setSteering(new WanderSteering(
				data.ownerID,
				data.targetPos));

			break;
		}
		case Steering::WANDER_AND_CHASE:
		{
			setSteering(new WanderAndChaseSteering(
				data.ownerID,
				data.targetPos,
				data.targetID));

			break;
		}
		case Steering::FLOCK:
		{
			setSteering(new FlockSteering(
				data.ownerID));

			break;
		}
		default: {}
	};
}

void SteeringComponent::setSteering(Steering* steering)
{
	delete mp_steering;
	mp_steering = steering;
}