#include "ChaseState.h"
#include "GameObjectManager.h"
#include "PositionComponent.h"
#include "Unit.h"

void ChaseState::onEntrance()
{
	//Change Sprite to chasing sprite
	mPrevPlayerLoc = Vec3(INFINITY, INFINITY, INFINITY);
	mSpriteChange = true;
}

void ChaseState::onExit()
{
}

StateTransition * ChaseState::update(Unit* currentUnit)
{
	if (mSpriteChange)
	{
		currentUnit->changeSprite("chase");
		mSpriteChange = false;
	}

	Vec3 playerLoc = OBJECT_MANAGER->findByID<Unit>(Unit::getPlayerID())->getPositionComponent()->getPosition();
	Vec3 currentLoc = currentUnit->getPositionComponent()->getPosition();
	Vec3 closestNode = currentUnit->getNavMesh()->getClosestVert(playerLoc);
	if (closestNode != mPrevPlayerLoc)
	{
		currentUnit->findPath(closestNode);
		mPrevPlayerLoc = closestNode;
	}


	if (glm::distance(playerLoc, currentLoc) > TEMP_DIST_IDLE)
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
