#include "Input.h"
#include "EventSystem.h"
#include "Game.h"

Input* Input::sp_instance = NULL;


Vec2 Input::getMousePosition() const
{
	return Vec2(GRAPHICS->getLastX(), GRAPHICS->getLastY());
}

Input::Input()
{	
}

Input::~Input()
{
	clear();
}


bool Input::setup()
{
	Keyboard::createInstance();
	Mouse::createInstance();

	return true;
}

void Input::clear()
{
	Keyboard::destroyInstance();
	Mouse::destroyInstance();
}


void Input::beginStep()
{
	KEYBOARD->beginStep();
	MOUSE->beginStep();
}

void Input::endStep()
{
	KEYBOARD->endStep();
	MOUSE->endStep();
}