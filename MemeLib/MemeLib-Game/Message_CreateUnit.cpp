#include "Message_CreateUnit.h"
#include "Game.h"
#include "GameMessageManager.h"
#include "UnitManager.h"
#include "ResourceManager.h"
#include "Graphics.h"

Message_CreateUnit::Message_CreateUnit() 
	: GameMessage(MSG_CREATE_UNIT)
{
}

Message_CreateUnit::~Message_CreateUnit()
{
}

void Message_CreateUnit::process()
{
	/*
	Vector2 size = { GRAPHICS->getWindowSize().x, GRAPHICS->getWindowSize().y };
	Vector2 pos = (size * 0.5f);

	Texture2D* m_texture = RESOURCES->getTexture2D("harambe");
	Sprite m_sprite = Sprite(m_texture);
	Unit* p_unit = UNITS->createRandomUnit(m_sprite);

	p_unit->setShowTarget(true);
	p_unit->setSteering(Steering::FLOCK, pos, PLAYER_UNIT_ID);
	*/
}