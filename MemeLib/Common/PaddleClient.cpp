#include "PaddleClient.h"
#include "ResourceManager.h"
#include "LinkingContext.h"
#include "PongApp.h"
PaddleClient::PaddleClient()
{
	mp_sprite = RESOURCES->getSprite("paddle1");
	mp_sprite->setScale(Vec3(0.23f, 1.0f, 1.f));
	mp_sprite->setRotation(Vec3(0, 180, 0) * Maths::DEG_TO_RAD);
	mFirstMove = true;
}


PaddleClient::~PaddleClient()
{
}

void PaddleClient::draw()
{
	mp_sprite->setPosition(m_pos);
	mp_sprite->draw(*GRAPHICS->getCamera());
}

void PaddleClient::updateClient()
{
	m_pos += m_dir * 0.015f * TIME->deltaTime();
}

void PaddleClient::write(RakNet::BitStream & stream) 
{
	stream.Write(m_pos.x);
	stream.Write(m_pos.y);
	stream.Write(m_pos.z);
}

void PaddleClient::sendToServer(RakNet::BitStream & stream)
{
	stream.Write(LINKING->getNetworkId(this, true));
	stream.Write(mClassId);
	write(stream);
}

void PaddleClient::sendToServer(RakNet::RakPeerInterface * peer)
{
	RakNet::BitStream stream;
	stream.Write((RakNet::MessageID)REPLICATION_PACKET);
	stream.Write(LINKING->getNetworkId(this, true));
	stream.Write(mClassId);
	write(stream);
	peer->Send(&stream, HIGH_PRIORITY, UNRELIABLE, 0, peer->GetSystemAddressFromIndex(0), false);
}

void PaddleClient::read(RakNet::BitStream & stream)
{
	if (mFirstMove)
	{
		stream.Read(m_pos.x);
		stream.Read(m_pos.y);
		stream.Read(m_pos.z);
		mFirstMove = false;
		return;
	}

	Vec3 tmp = m_pos;
	Vec3 tmp2;
	stream.Read(tmp2.x);
	stream.Read(tmp2.y);
	stream.Read(tmp2.z);
	m_pos = tmp2;
	m_dir = tmp - m_pos;
}

void PaddleClient::writeToFile(std::ofstream & of)
{

}