#include "InputState.h"
#include "Input.h"

bool InputState::write(RakNet::BitStream & stream) const
{
	return false;
}

bool InputState::read(RakNet::BitStream & stream)
{
	return false;
}

void InputState::update(float deltaTime)
{
	if (INPUT->getKey(Keyboard::W))
	{
		mDesiredForwardAmount -= .05f;
		std::cout << "UP\n";
	}

	if (INPUT->getKey(Keyboard::S))
	{
		mDesiredForwardAmount += .05f;
		std::cout << "DOWN\n";
	}
}
