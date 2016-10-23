#include "Message_ExitApplication.h"
#include "Game.h"
#include "GameMessageManager.h"
#include "UnitManager.h"

Message_ExitApplication::Message_ExitApplication()
	: GameMessage(MSG_EXIT_APPLICATION)
{
}

Message_ExitApplication::~Message_ExitApplication()
{
}

void Message_ExitApplication::process()
{
	//GAME->requestStop();
}

