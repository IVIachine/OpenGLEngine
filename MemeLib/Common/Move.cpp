#include "Move.h"

bool Move::write(RakNet::BitStream & stream) const
{
	mInputState.write(stream);
	stream.Write(mDeltaTime);
	return true;
}

bool Move::read(RakNet::BitStream & stream)
{
	mInputState.read(stream);
	stream.Read(mDeltaTime);
	return true;
}
