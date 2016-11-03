#include "Archer.h"



Archer::Archer()
{
}


Archer::~Archer()
{
}

void Archer::write(RakNet::BitStream & stream) const
{
	stream.Write(mCurrentAction);
	stream.Write(mHealth);
	stream.Write(LINKING->GetNetworkId(mTownCenter, false));
}

void Archer::read(RakNet::BitStream & stream)
{
	stream.Read(mCurrentAction);
	stream.Read(mHealth);
	uint32_t centerID;
	stream.Read(centerID);
	mTownCenter = static_cast<TownCenter*>(LINKING->getGameObject(centerID, false, 0));
}

void Archer::send(RakNet::RakPeerInterface * peer)
{
	RakNet::BitStream stream;
	stream.Write((RakNet::MessageID)REPLICATION_PACKET);
	stream.Write(LINKING->GetNetworkId(this, true));
	stream.Write(mClassId);
	write(stream);
	peer->Send(&stream, HIGH_PRIORITY, UNRELIABLE, 0, peer->GetSystemAddressFromIndex(0), false);
}
