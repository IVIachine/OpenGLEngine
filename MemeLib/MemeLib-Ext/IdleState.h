#pragma once
#include "StateMachine.h"
class IdleState : public StateMachineState
{
public:
	IdleState(const SM_idType& id, int fireCount) :StateMachineState(id){};

	virtual void onEntrance();
	virtual void onExit();
	virtual StateTransition* update(Vec3 currentLoc);
private:

};

