#pragma once
#include "Trackable.h"
#include <glm.hpp>
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

