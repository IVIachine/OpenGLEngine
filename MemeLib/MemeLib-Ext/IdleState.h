#pragma once
#include "StateMachine.h"

#define TEMP_DIST 1 //To Be Removed
class Timer;

class IdleState : public StateMachineState
{
public:
	IdleState(const SM_idType& id);
	virtual ~IdleState();
	virtual void onEntrance();
	virtual void onExit();
	virtual StateTransition* update(Unit* currentUnit);
private:
	Timer* mpTimeTillSwitch;
};

