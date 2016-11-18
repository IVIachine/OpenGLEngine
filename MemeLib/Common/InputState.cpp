#include "InputState.h"
#include "Input.h"

bool InputState::write(RakNet::BitStream & stream) const
{
	stream.Write(mDesiredBackAmount);
	stream.Write(mDesiredForwardAmount);
	return true;
}

bool InputState::read(RakNet::BitStream & stream)
{
	stream.Read(mDesiredBackAmount);
	stream.Read(mDesiredForwardAmount);
	return true;
}

void InputState::update(float deltaTime)
{
	if (INPUT->getKey(Keyboard::W))
	{
		mDesiredForwardAmount += .05f;
	}

	if (INPUT->getKey(Keyboard::S))
	{
		mDesiredForwardAmount -= .05f;
	}
}
