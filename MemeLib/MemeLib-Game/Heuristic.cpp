#include "Heuristic.h"
#include "Game.h"
#include "Node.h"
#include "Vector3.h"

Heuristic::Heuristic(Node* goalNode)
{
	mpGoalNode = goalNode;
}


Heuristic::~Heuristic()
{
}

float Heuristic::getEstimate(Node * testNode)
{
	Vec3 secondLoc = testNode->getPosition();

	return Vector3::distance(mpGoalNode->getPosition(), secondLoc);
}