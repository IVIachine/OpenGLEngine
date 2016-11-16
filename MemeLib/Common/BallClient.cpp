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
	mp_sprite->setPosition(mLoc);
	mp_sprite->draw(*GRAPHICS->getCamera());
}

void BallClient::update()
{
}

void BallClient::write(RakNet::BitStream & stream) const
{
	stream.Write(mLoc.x);
	stream.Write(mLoc.y);
	stream.Write(mLoc.z);
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
	stream.Read(mLoc.x);
	stream.Read(mLoc.y);
	stream.Read(mLoc.z);
	setLoc(mLoc);
}

void BallClient::writeToFile(std::ofstream & of)
{

}