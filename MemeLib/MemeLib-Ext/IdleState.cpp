#include "IdleState.h"
#include "Unit.h"
#include "GameObjectManager.h"
#include "PositionComponent.h"

void IdleState::onEntrance()
{
}

void IdleState::onExit()
{
}

StateTransition * IdleState::update(Vec3 currentLoc)
{
	for (auto object : OBJECT_MANAGER->getData())
	{
		std::cout << object.first << std::endl;
	}


	//Check dist from all powerups



	//If distances are a below the threshhold, change states
	return nullptr;
}
