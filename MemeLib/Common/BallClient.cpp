#include "BallClient.h"
#include "ResourceManager.h"
#include "Graphics.h"
#include "LinkingContext.h"

BallClient::BallClient()
{
	mp_sprite = RESOURCES->getSprite("ball");
	mp_sprite->setScale(Vec3(0.211f, 0.211f, 1.f));
	mp_sprite->setRotation(Vec3(0, 180, 0) * Maths::DEG_TO_RAD);
}


BallClient::~BallClient()
{
}

void BallClient::draw()
{
	mp_sprite->setPosition(m_posOld);
	mp_sprite->draw(*GRAPHICS->getCamera());
}

void BallClient::update()
{
}

void BallClient::write(RakNet::BitStream & stream) const
{
	stream.Write(m_posOld.x);
	stream.Write(m_posOld.y);
	stream.Write(m_posOld.z);
}

void BallClient::sendToServer(RakNet::BitStream & stream)
{
	stream.Write(LINKING->getNetworkId(this, true));
	stream.Write(mClassId);
	write(stream);
}

void BallClient::sendToServer(RakNet::RakPeerInterface * peer)
{
	RakNet::BitStream stream;
	stream.Write((RakNet::MessageID)REPLICATION_PACKET);
	stream.Write(LINKING->getNetworkId(this, true));
	stream.Write(mClassId);
	write(stream);
	peer->Send(&stream, HIGH_PRIORITY, UNRELIABLE, 0, peer->GetSystemAddressFromIndex(0), false);
}

void BallClient::read(RakNet::BitStream & stream)
{
	m_posOld = m_posNew;

	stream.Read(m_posNew.x);
	stream.Read(m_posNew.y);
	stream.Read(m_posNew.z);
}

void BallClient::writeToFile(std::ofstream & of)
{

}