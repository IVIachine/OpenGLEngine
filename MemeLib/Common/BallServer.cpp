#include "BallServer.h"
#include "LinkingContext.h"
#include "GameTime.h"

BallServer::BallServer()
{
	m_ballSpeed = 0.0001f;

	float rx = m_ballSpeed;
	float ry = 0.f;

	m_vel = Vec3(rx, ry, 0.f);
}


BallServer::~BallServer()
{
}

void BallServer::update()
{
	//Update physics here

	m_pos = m_pos + m_vel;
}

void BallServer::write(RakNet::BitStream & stream) const
{
	stream.Write(m_pos.x);
	stream.Write(m_pos.y);
	stream.Write(m_pos.z);
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
	stream.Read(m_pos.x);
	stream.Read(m_pos.y);
	stream.Read(m_pos.z);
	setLoc(m_pos);
}

void BallServer::writeToFile(std::ofstream & of)
{

}

void BallServer::draw()
{
}