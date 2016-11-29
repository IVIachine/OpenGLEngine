#include "ChaseState.h"
#include "GameObjectManager.h"
#include "PositionComponent.h"
#include "Unit.h"

void ChaseState::onEntrance()
{
	//Change Sprite to chasing sprite
	mPrevPlayerLoc = Vec3(INFINITY, INFINITY, INFINITY);
	std::cout << "CHASE\n";
}

void ChaseState::onExit()
{
}

StateTransition * ChaseState::update(Unit* currentUnit)
{
	Vec3 playerLoc = static_cast<Unit*>(OBJECT_MANAGER->getData()[PLAYER_ID])->getPositionComponent()->getPosition();
	Vec3 currentLoc = currentUnit->getPositionComponent()->getPosition();
	Vec3 closestNode = currentUnit->getNavMesh()->getClosestVert(playerLoc);
	if (closestNode != mPrevPlayerLoc)
	{
		currentUnit->findPath(closestNode);
		mPrevPlayerLoc = closestNode;
		std::cout << "Attempt\n";
	}


	if (glm::distance(playerLoc, currentLoc) > TEMP_DIST)
	{
		std::map<TransitionType, StateTransition*>::iterator iter = mTransitions.find(IDLE_TRANSITION);
		if (iter != mTransitions.end())//found?
		{
			StateTransition* pTransition = iter->second;
			return pTransition;
		}
	}

	return NULL;
}
