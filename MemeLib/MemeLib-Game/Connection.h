#ifndef _CONNECTION_H_
#define _CONNECTION_H_

#include <Trackable.h>

class Node;

class Connection : public Trackable
{
public:
	Connection(Node* pSource, Node* pTarget);
	Connection(Node* pSource, Node* pTarget, float moveCost, bool isWalkable);
	~Connection();

	Node*	getSource() const;
	Node*	getTarget() const;

	float	moveCost();
	bool	isWalkable();
	bool	isDiagonal();

private:
	Node*	mpSource;
	Node*	mpTarget;

	float	mMoveCost;
	bool	mIsWalkable;
};

#endif // !_CONNECTION_H_
