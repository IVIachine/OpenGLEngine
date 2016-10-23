#include "Message_DeleteUnit.h"
#include "Game.h"
#include "GameMessageManager.h"
#include "UnitManager.h"

Message_DeleteUnit::Message_DeleteUnit() : GameMessage(MSG_DELETE_UNIT)
{
}

Message_DeleteUnit::~Message_DeleteUnit()
{
}

void Message_DeleteUnit::process()
{
	UNITS->deleteRandomUnit();
}