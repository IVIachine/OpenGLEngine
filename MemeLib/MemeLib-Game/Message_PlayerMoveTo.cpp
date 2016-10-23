#include "Message_PlayerMoveTo.h"
#include "Game.h"
#include "GameMessageManager.h"
#include "UnitManager.h"

Message_PlayerMoveTo::Message_PlayerMoveTo(const Vector2& position) : 
	GameMessage(MSG_PLAYER_MOVE_TO), mPos(position)
{
}

Message_PlayerMoveTo::~Message_PlayerMoveTo()
{
}

void Message_PlayerMoveTo::process()
{
	Unit* pPlayer = UNITS->getPlayerUnit();
	if (pPlayer != NULL)
	{
		pPlayer->setSteering(Steering::ARRIVE_AND_FACE, mPos);
	}
}

