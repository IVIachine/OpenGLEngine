#include "IdleState.h"

void IdleState::onEntrance()
{
}

void IdleState::onExit()
{
}

StateTransition * IdleState::update(Vec3 currentLoc)
{
	Vec3 playerPos = static_cast<Unit*>(OBJECT_MANAGER->getData().at(PLAYER_ID))->getPositionComponent()->getPosition();//Access the player unit location

	//Check player dist from current Loc




	//Check dist from all powerups



	//If distances are a below the threshhold, change states
}
