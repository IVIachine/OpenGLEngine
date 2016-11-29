#pragma once
#pragma once
#include "StateMachine.h"
#include "Vector3.h"
#include "Pickup.h"

#define TEMP_DIST .5f //To Be Removed

class PickupState : public StateMachineState
{
public:
	PickupState(const SM_idType& id);
	virtual ~PickupState() {};
	virtual void onEntrance();
	virtual void onExit();
	virtual StateTransition* update(Unit* currentUnit);
private:
	Pickup* mPickup;
	bool mHasSetPath;
};
