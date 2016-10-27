#pragma once
#include "Trackable.h"
#include "Vector3.h"

class Node;

class Heuristic :public Trackable
{
private:
	Node* mpGoalNode;
public:
	Heuristic(Node* goalNode);
	~Heuristic();

	float getEstimate(Node* testNode);
};

