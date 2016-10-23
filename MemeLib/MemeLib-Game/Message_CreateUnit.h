#ifndef _MSG_CREATE_UNIT_H_
#define _MSG_CREATE_UNIT_H_

#include "GameMessage.h"
#include "Vector2.h"

/// <summary>
/// Create a unit at a random location on the screen and have it run the WanderAndChase steering behavior.
/// </summary>
class Message_CreateUnit : public GameMessage
{
public:
	Message_CreateUnit();
	~Message_CreateUnit();

	void process();

private:

};

#endif // !_MSG_CREATE_UNIT_H_
