#include "ComponentManager.h"
#include "SteeringComponent.h"
#include "SeekSteering.h"
#include "PathFollowSteering.h"

SteeringComponent::SteeringComponent(const ComponentID& id, const ComponentID& physicsComponentID)
	:Component(id)
	, mPhysicsComponentID(physicsComponentID)
	, mpSteering(NULL)
{
}

SteeringComponent::~SteeringComponent()
{
	delete mpSteering;
}

void SteeringComponent::applySteering(PhysicsComponent& physicsComponent)
{
	if (mpSteering != NULL)
	{
		//allow Steering to run
		mpSteering->update();
		//set physics data to that of the Steering
		physicsComponent.setData(mpSteering->getData());
		//update component's data
		mData.targetLoc = mpSteering->getTargetLoc();
	}
}

void SteeringComponent::setData(const SteeringData& data, Path path)
{
	mData = data;

	switch (data.type)
	{
	case Steering::PATH_FOLLOW:
	{
		//cleanup old steering - todo: check for already existing steering and reuse if possible
		delete mpSteering;
		//create new steering
		mpSteering = new PathFollowSteering(data.ownerID, data.targetLoc, data.targetID, .25f);
		dynamic_cast<PathFollowSteering*>(mpSteering)->setPath(path);
		break;
	}
	case Steering::FLEE:
	{
		mpSteering = new SeekSteering(data.ownerID, data.targetLoc, data.targetID, true);
		break;
	}
	case Steering::ARRIVE:
	{
		
		break;
	}
	default:
	{

	}
	};
}

