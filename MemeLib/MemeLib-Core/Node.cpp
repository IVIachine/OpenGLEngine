#include "Node.h"

Node::Node()
	: mId(BAD_NODE_ID), mX(0), mY(0), mZ(0)
{
}

Node::Node(const NODE_ID & id, const glm::vec3& pos)
	: mId(id), mX(pos.x), mY(pos.y), mZ(pos.z)
{
}

Node::Node(const NODE_ID& id, float x, float y, float z)
	: mId(id), mX(x), mY(y), mZ(z)
{
}

Node::~Node()
{
}


const NODE_ID& Node::getId() const
{
	return mId;
}

float Node::getX() const
{
	return mX;
}

float Node::getY() const
{
	return mY;
}

float Node::getZ() const
{
	return mZ;
}

glm::vec3 Node::getPosition() const
{
	return{ mX, mY, mZ };
}