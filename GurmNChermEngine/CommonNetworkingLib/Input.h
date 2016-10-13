#ifndef _INPUT_H_
#define _INPUT_H_

#include <SFML\Window\Keyboard.hpp>
#include <SFML\Window\Mouse.hpp>
#include <iostream>
#include <string>
#include <cassert>
#include "RakPeerInterface.h"

#include "Keyboard.h"
#include "Mouse.h"

#define INPUT Input::getInstance()

class Input
{
public:
	static Input*	getInstance();
	static Input*	createInstance();
	static void		destroyInstance();

	void setup();
	void cleanup();

	void beginStep();
	void endStep();

	bool getKey(Keyboard::Keys key) { return KEYBOARD->getKey(key); }
	bool getKeyDown(Keyboard::Keys key) { return KEYBOARD->getKeyDown(key); }
	bool getKeyUp(Keyboard::Keys key) { return KEYBOARD->getKeyUp(key); }

	bool getButton(Mouse::Buttons button) { return MOUSE->getButton(button); }
	bool getButtonDown(Mouse::Buttons button) { return MOUSE->getButtonDown(button); }
	bool getButtonUp(Mouse::Buttons button) { return MOUSE->getButtonUp(button); }

	char getChar() const;

private:
	Input();
	~Input();

	std::string m_textEntered = "";

	static Input* sp_instance;
};

#endif // !_INPUT_H_
