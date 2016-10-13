#include "Input.h"
#include "EventSystem.h"
#include "Game.h"

Input* Input::sp_instance = NULL;


Input::Input()
{
	setup();
}

Input::~Input()
{
	cleanup();
}


Input* Input::getInstance()
{
	assert(sp_instance != NULL);
	return sp_instance;
}

void Input::destroyInstance()
{
	delete sp_instance;
	sp_instance = NULL;
}

Input* Input::createInstance()
{
	sp_instance = new Input();
	return getInstance();
}


void Input::setup()
{
	Keyboard::createInstance();
	Mouse::createInstance();
}

void Input::cleanup()
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


char Input::getChar() const
{
	char c = GRAPHICS->s_getChar;

	GRAPHICS->s_getChar = '\0';

	return c;
}