#include "GameObject.h"

GameObject::GameObject()
{
	m_id = INVALID_GOBJ_ID;
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


void GameObject::sendToServer(RakNet::RakPeerInterface * peer)
{
}

void GameObject::sendToServer(RakNet::BitStream & stream)
{
}

void GameObject::write(RakNet::BitStream & stream)
{
}

void GameObject::writeToFile(std::ofstream & of)
{
}

void GameObject::read(RakNet::BitStream & stream)
{
}