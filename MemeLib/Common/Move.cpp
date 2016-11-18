#include "Move.h"

bool Move::write(RakNet::BitStream & stream) const
{
	mInputState.write(stream);
	stream.Write(mDeltaTime);
	stream.Write(mTimestamp);
	return true;
}

bool Move::read(RakNet::BitStream & stream)
{
	mInputState.read(stream);
	stream.Read(mDeltaTime);
	stream.Read(mTimestamp);
	return true;
}
