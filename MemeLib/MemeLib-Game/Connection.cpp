#include "Node.h"
#include "Connection.h"

Connection::Connection(Node* pSource, Node* pTarget)
{
	mpSource = pSource;
	mpTarget = pTarget;

	mMoveCost = 1.0f;
	mIsWalkable = true;
}

Connection::Connection(Node* pSource, Node* pTarget, float moveCost, bool isWalkable)
{
	mpSource = pSource;
	mpTarget = pTarget;

	mMoveCost = moveCost;
	mIsWalkable = isWalkable;
}

Connection::~Connection()
{
}


Node* Connection::getSource() const
{
	return mpSource;
}

Node* Connection::getTarget() const
{
	return mpTarget;
}


float Connection::moveCost()
{
	return mMoveCost;
}

bool Connection::isWalkable()
{
	return mIsWalkable;
}

bool Connection::isDiagonal()
{
	Vec3 sPos = mpSource->getPosition();
	Vec3 tPos = mpSource->getPosition();

	return
		(sPos.x != tPos.x && sPos.y != tPos.y) ||
		(sPos.x != tPos.x && sPos.z != tPos.z) ||
		(sPos.y != tPos.y && sPos.z != tPos.z);
}