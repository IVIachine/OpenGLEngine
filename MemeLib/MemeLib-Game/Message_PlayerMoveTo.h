#ifndef _MSG_PLAYER_MOVE_TO_H_
#define _MSG_PLAYER_MOVE_TO_H_

#include "GameMessage.h"
#include "Vector2.h"

class Vector2;

/// <summary>
/// Direct player Unit to location using ArriveAndFaceSteering.
/// </summary>
class Message_PlayerMoveTo : public GameMessage
{
public:
	Message_PlayerMoveTo(const Vector2& position);
	~Message_PlayerMoveTo();

	void process();

private:
	Vector2 mPos;
};

#endif // !_MSG_PLAYER_MOVE_TO_H_