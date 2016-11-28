#pragma once
#include "StateMachine.h"

#define TEMP_DIST 100 //To Be Removed

class IdleState : public StateMachineState
{
public:
	IdleState(const SM_idType& id) :StateMachineState(id){};

	virtual void onEntrance();
	virtual void onExit();
	virtual StateTransition* update(Vec3 currentLoc);
private:

};

