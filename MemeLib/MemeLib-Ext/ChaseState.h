#pragma once
#include "StateMachine.h"
#include "Vector3.h"

#define TEMP_DIST_IDLE 2 //To Be Removed

class ChaseState : public StateMachineState
{
public:
	ChaseState(const SM_idType& id) :StateMachineState(id) {};

	virtual void onEntrance();
	virtual void onExit();
	virtual StateTransition* update(Unit* currentUnit);
private:
	Vec3 mPrevPlayerLoc;
};

