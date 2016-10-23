#include "Node.h"

Node::Node()
	:mId(BAD_NODE_ID)
{
}

Node::Node(const NODE_ID& id, glm::vec3 pos)
	: mId(id), mPos(pos)
{
}

Node::~Node()
{
}