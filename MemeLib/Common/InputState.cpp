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
	float speed = deltaTime * 0.015f;

	if (INPUT->getKey(Keyboard::W))
	{
		mDesiredForwardAmount += speed;
	}

	if (INPUT->getKey(Keyboard::S))
	{
		mDesiredBackAmount += speed;
	}
}
