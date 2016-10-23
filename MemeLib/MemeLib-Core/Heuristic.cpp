#include "Heuristic.h"
#include "Game.h"
#include "Node.h"

Heuristic::Heuristic(Node* goalNode)
{
	mpGoalNode = goalNode;
}


Heuristic::~Heuristic()
{
}

//CITE: http://theory.stanford.edu/~amitp/GameProgramming/Heuristics.html#S7
float Heuristic::getEstimate(Node * testNode)
{
	glm::vec3 secondLoc = testNode->getPosition();
	float dx = abs(secondLoc.x - mpGoalNode->getPosition().x);
	float dy = abs(secondLoc.y - mpGoalNode->getPosition().y);
	float dz = abs(secondLoc.z - mpGoalNode->getPosition().z);
	return (dx + dy + dz) + float(sqrt(2) - 2) * min(dx, dy, dz);
}