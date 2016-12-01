#include "PickupState.h"
#include "Unit.h"
#include "PositionComponent.h"
#include "GameobjectManager.h"
#include "UnitManager.h"

PickupState::PickupState(const SM_idType & id)
	:StateMachineState(id)
{
	mHasSetPath = false;
}

void PickupState::onEntrance()
{
	//Change sprite
	mHasSetPath = false;
	mSpriteChange = true;
}

void PickupState::onExit()
{
}

StateTransition * PickupState::update(Unit * currentUnit)
{
	if (!currentUnit)
	{
		std::cout << "CURRENT UNIT IS NULL\n";

		return NULL;
	}

	if (mSpriteChange)
	{
		currentUnit->changeSprite("pickup");
		mSpriteChange = false;
	}

	Unit* pPlayer = UNITS->getUnit(Unit::getPlayerID());
	if (!pPlayer)
	{
		std::cout << toString() << " PLAYER IS NULL\n";
		return NULL;
	}

	Vec3 playerLoc = pPlayer->getPositionComponent()->getPosition();
	Vec3 currentLoc = currentUnit->getPositionComponent()->getPosition();
	if (glm::distance(playerLoc, currentLoc) < TEMP_DIST_CHASE)
	{
		std::map<TransitionType, StateTransition*>::iterator iter = mTransitions.find(CHASE_TRANSITION);
		if (iter != mTransitions.end())//found?
		{
			StateTransition* pTransition = iter->second;
			currentUnit->getPathFinder()->setState(AStarState::Idle);
			return pTransition;
		}
	}

	if (OBJECT_MANAGER->idExists(mPickup))
	{
		Pickup* tmp = OBJECT_MANAGER->findByID<Pickup>(mPickup);
		if (!mHasSetPath)
		{
			currentUnit->findPath(tmp->getLoc());
			mHasSetPath = true;
		}

		float dist = glm::distance(currentUnit->getPositionComponent()->getPosition(), tmp->getLoc());
		if (dist < TEMP_DIST_PICKUP)
		{
			currentUnit->applyBuff(OBJECT_MANAGER->findByID<Pickup>(mPickup));
			OBJECT_MANAGER->removeByID(mPickup);
			mPickup = INVALID_GOBJ_ID;
			std::map<TransitionType, StateTransition*>::iterator iter = mTransitions.find(IDLE_TRANSITION);
			if (iter != mTransitions.end())//found?
			{
				StateTransition* pTransition = iter->second;
				return pTransition;
			}
		}
	}
	else
	{
		mPickup = INVALID_GOBJ_ID;
		std::map<TransitionType, StateTransition*>::iterator iter = mTransitions.find(IDLE_TRANSITION);
		if (iter != mTransitions.end())//found?
		{
			StateTransition* pTransition = iter->second;
			return pTransition;
		}
	}
	return NULL;
}
