#include "GameObject.h"

void GameObject::sendToServer(RakNet::RakPeerInterface * peer)
{
}

void GameObject::sendToServer(RakNet::BitStream & stream)
{
}

void GameObject::write(RakNet::BitStream & stream)
{
}

void GameObject::read(RakNet::BitStream & stream)
{
}

GameObject::GameObject()
{
}

GameObject::~GameObject()
{
}


bool GameObject::start()
{
	return true;
}

void GameObject::destroy()
{
}

void GameObject::update()
{
}

void GameObject::draw()
{

}

void GameObject::handleEvent(const Event & ev)
{
}
