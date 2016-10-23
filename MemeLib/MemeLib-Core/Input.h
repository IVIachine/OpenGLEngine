#ifndef _INPUT_H_
#define _INPUT_H_

#include <iostream>
#include <string>
#include <cassert>

#include "Keyboard.h"
#include "Mouse.h"

#ifndef INPUT
#define INPUT Input::getInstance()
#endif // !INPUT

class Input
{
public:
	static Input*	getInstance()
	{
		assert(sp_instance != NULL);
		return sp_instance;
	};
	static Input*	createInstance()
	{
		sp_instance = new Input();
		return getInstance();
	};
	static void		destroyInstance()
	{
		delete sp_instance;
		sp_instance = NULL;
	};

	bool setup();
	void cleanup();

	void beginStep();
	void endStep();

	bool getKey(Keyboard::KeyCode key) { return KEYBOARD->getKey(key); }
	bool getKeyDown(Keyboard::KeyCode key) { return KEYBOARD->getKeyDown(key); }
	bool getKeyUp(Keyboard::KeyCode key) { return KEYBOARD->getKeyUp(key); }

	bool getButton(Mouse::Buttons button) { return MOUSE->getButton(button); }
	bool getButtonDown(Mouse::Buttons button) { return MOUSE->getButtonDown(button); }
	bool getButtonUp(Mouse::Buttons button) { return MOUSE->getButtonUp(button); }

private:
	Input();
	~Input();

	std::string m_textEntered = "";

	static Input* sp_instance;
};

#endif // !_INPUT_H_
