#include "BallServer.h"
#include "LinkingContext.h"


BallServer::BallServer()
{
}


BallServer::~BallServer()
{
}

void BallServer::update()
{
	//Update physics here
}

void BallServer::write(RakNet::BitStream & stream) const
{
	stream.Write(mLoc.x);
	stream.Write(mLoc.y);
	stream.Write(mLoc.z);
}

void BallServer::sendToServer(RakNet::BitStream & stream)
{
	stream.Write(LINKING->getNetworkId(this, true));
	stream.Write(mClassId);
	write(stream);
}

void BallServer::sendToServer(RakNet::RakPeerInterface * peer)
{
	RakNet::BitStream stream;
	stream.Write((RakNet::MessageID)REPLICATION_PACKET);
	stream.Write(LINKING->getNetworkId(this, true));
	stream.Write(mClassId);
	write(stream);
	peer->Send(&stream, HIGH_PRIORITY, UNRELIABLE, 0, peer->GetSystemAddressFromIndex(0), false);
}

void BallServer::read(RakNet::BitStream & stream)
{
	stream.Read(mLoc.x);
	stream.Read(mLoc.y);
	stream.Read(mLoc.z);
	setLoc(mLoc);
}

void BallServer::writeToFile(std::ofstream & of)
{

}

void BallServer::draw()
{
}
