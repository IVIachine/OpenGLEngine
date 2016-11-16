#include "Paddle.h"
#include "ResourceManager.h"
#include "LinkingContext.h"

Paddle::Paddle()
{
}


Paddle::~Paddle()
{
}

void Paddle::write(RakNet::BitStream & stream) const
{
}

void Paddle::sendToServer(RakNet::BitStream & stream)
{
}

void Paddle::sendToServer(RakNet::RakPeerInterface * peer)
{
}

void Paddle::read(RakNet::BitStream & stream)
{
}

void Paddle::writeToFile(std::ofstream & of)
{
}

void Paddle::draw()
{
}

void Paddle::update()
{
}
