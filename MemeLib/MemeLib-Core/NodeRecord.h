#pragma once
#include "Connection.h"
#include "Node.h"
#include <algorithm>
#include <list>

struct NodeRecord : public Node
{
	Node* mpNode;
	Connection* mpConnection;
	float mCostSoFar;
	float mEstimatedTotalCost;
};



