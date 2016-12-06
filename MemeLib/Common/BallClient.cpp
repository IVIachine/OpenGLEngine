#include "BallClient.h"
#include "ResourceManager.h"
#include "Graphics.h"
#include "LinkingContext.h"
#include "GameTime.h"

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
	mp_sprite->setPosition(m_posCurrent);
	mp_sprite->draw(*GRAPHICS->getCamera());
}

void BallClient::update(float lerpTime)
{
	m_posCurrent = Vector3::lerp(m_posCurrent, m_posNew, lerpTime * TIME->deltaTime());
}

void BallClient::write(RakNet::BitStream & stream) const
{
	stream.Write(m_posNew.x);
	stream.Write(m_posNew.y);
	stream.Write(m_posNew.z);
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
	m_posOld = m_posCurrent;

	stream.Read(m_posNew.x);
	stream.Read(m_posNew.y);
	stream.Read(m_posNew.z);
	//std::cout << m_posOld.x << " " << m_posOld.z << " | " << m_posNew.x << " " << m_posNew.z << std::endl;
}

void BallClient::writeToFile(std::ofstream & of)
{

}