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
	glm::vec3 secondLoc = testNode->getPos();
	float dx = abs(secondLoc.x - mpGoalNode->getPos().x);
	float dy = abs(secondLoc.y - mpGoalNode->getPos().y);
	return (dx + dy) + float(sqrt(2) - 2) * min(dx, dy);
}