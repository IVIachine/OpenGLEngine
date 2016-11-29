#include "PickupState.h"
#include "Unit.h"
#include "PositionComponent.h"

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
	if (!mHasSetPath)
	{
		currentUnit->findPath(mPickupLoc);
		mHasSetPath = true;
	}

	if (glm::distance(currentUnit->getPositionComponent()->getPosition(), mPickupLoc) < TEMP_DIST)
	{

	}

	return NULL;
}
