#include "PaddleClient.h"
#include "ResourceManager.h"
#include "LinkingContext.h"
#include "PongApp.h"
PaddleClient::PaddleClient()
{
	mp_sprite = RESOURCES->getSprite("paddle1");
	mp_sprite->setScale(Vec3(0.23f, 1.0f, 1.f));
	mp_sprite->setRotation(Vec3(0, 180, 0) * Maths::DEG_TO_RAD);
}


PaddleClient::~PaddleClient()
{
}

void PaddleClient::draw()
{
	mp_sprite->setPosition(mLoc);
	mp_sprite->draw(*GRAPHICS->getCamera());
}

void PaddleClient::update()
{
}

void PaddleClient::write(RakNet::BitStream & stream) 
{
	stream.Write(mLoc.x);
	stream.Write(mLoc.y);
	stream.Write(mLoc.z);
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
	stream.Read(mLoc.x);
	stream.Read(mLoc.y);
	stream.Read(mLoc.z);
	setLoc(mLoc);
}

void PaddleClient::writeToFile(std::ofstream & of)
{

}