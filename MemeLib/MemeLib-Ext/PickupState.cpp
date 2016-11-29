#include "PickupState.h"
#include "Unit.h"
#include "PositionComponent.h"
#include "GameobjectManager.h"

PickupState::PickupState(const SM_idType & id)
	:StateMachineState(id)
{
	mHasSetPath = false;
}

void PickupState::onEntrance()
{
	//Change sprite
	mHasSetPath = false;
}

void PickupState::onExit()
{
}

StateTransition * PickupState::update(Unit * currentUnit)
{
	if (OBJECT_MANAGER->findByID(mPickup->getID()) != NULL)
	{
		if (!mHasSetPath)
		{
			currentUnit->findPath(mPickup->getLoc());
			mHasSetPath = true;
		}

		if (glm::distance(currentUnit->getPositionComponent()->getPosition(), mPickup->getLoc()) < TEMP_DIST)
		{
			OBJECT_MANAGER->removeByID(mPickup->getID());
			std::cout << "INCREASING STATS\n";
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
		std::map<TransitionType, StateTransition*>::iterator iter = mTransitions.find(IDLE_TRANSITION);
		if (iter != mTransitions.end())//found?
		{
			StateTransition* pTransition = iter->second;
			return pTransition;
		}
	}
	return NULL;
}
