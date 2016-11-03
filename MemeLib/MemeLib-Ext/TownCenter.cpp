#include "TownCenter.h"



TownCenter::TownCenter()
{
}


TownCenter::~TownCenter()
{
}

void TownCenter::write(RakNet::BitStream & stream) const
{
	stream.Write(mType);
	stream.Write(mLoc.x);
	stream.Write(mLoc.y);
	stream.Write(mLoc.z);
	stream.Write(mHealth);
}

void TownCenter::send(RakNet::RakPeerInterface * peer)
{
	RakNet::BitStream stream;
	stream.Write((RakNet::MessageID)REPLICATION_PACKET);
	stream.Write(LINKING->GetNetworkId(this, true));
	stream.Write(mClassId);
	write(stream);
	peer->Send(&stream, HIGH_PRIORITY, UNRELIABLE, 0, peer->GetSystemAddressFromIndex(0), false);
}

void TownCenter::read(RakNet::BitStream & stream)
{
	stream.Read(mType);
	stream.Read(mLoc.x);
	stream.Read(mLoc.y);
	stream.Read(mLoc.z);
	stream.Read(mHealth);
}
