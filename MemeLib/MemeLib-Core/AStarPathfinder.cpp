#include "AStarPathfinder.h"
#include "Path.h"
#include "Connection.h"
#include "Game.h"
#include <PerformanceTracker.h>
#include "Graph.h"

AStarPathfinder::AStarPathfinder(Graph * pGraph)
	:Pathfinder(pGraph)
{
}

AStarPathfinder::~AStarPathfinder()
{
}

const Path & AStarPathfinder::findPath(Node * pFrom, Node * pTo)
{
	//allocate nodes to visit list and place starting node in it
	std::vector<Connection*> connections;
	std::list<NodeRecord*> nodesToVisit;
	std::list<NodeRecord*> visitedNodes;
	NodeRecord* endNodeRecord;
	NodeRecord* startRecord = new NodeRecord();
	startRecord->mpNode = pFrom;
	startRecord->mpConnection = NULL;
	startRecord->mCostSoFar = 0;
	nodesToVisit.push_back(startRecord);
	NodeRecord* currentNode = NULL;
	float endNodeHeuristic = 0.0f;
	mPath.clear();

	Heuristic theHeuristic(pTo);
	startRecord->mEstimatedTotalCost = theHeuristic.getEstimate(startRecord);

	while (nodesToVisit.size() > 0)
	{
		currentNode = getSmallestNode(nodesToVisit);
		if (currentNode->mpNode == pTo)
			break;

		connections = mpGraph->getConnections(currentNode->mpNode->getId());

		for (size_t i = 0; i < connections.size(); i++)
		{
			Node* endNode = connections[i]->getToNode();
			float endNodeCost = currentNode->mCostSoFar + connections[i]->getCost();

			if (containsNode(visitedNodes, endNode))
			{
				endNodeRecord = findNodeRecord(visitedNodes, endNode);

				if (endNodeRecord->mCostSoFar <= endNodeCost)
					continue;

				visitedNodes.remove(endNodeRecord);
				endNodeHeuristic = endNodeRecord->mEstimatedTotalCost - endNodeRecord->mCostSoFar;
			}
			else if (containsNode(nodesToVisit, endNode))
			{
				endNodeRecord = findNodeRecord(nodesToVisit, endNode);

				if (endNodeRecord->mCostSoFar <= endNodeCost)
					continue;

				endNodeHeuristic = endNodeRecord->mpConnection->getCost() - endNodeRecord->mCostSoFar;
			}
			else
			{
				endNodeRecord = new NodeRecord();
				endNodeRecord->mpNode = endNode;

				endNodeHeuristic = theHeuristic.getEstimate(endNode);
			}

			endNodeRecord->mCostSoFar = endNodeCost;
			endNodeRecord->mpConnection = connections[i];
			endNodeRecord->mEstimatedTotalCost = endNodeCost + endNodeHeuristic;

			if (!(containsNode(nodesToVisit, endNode)))
			{
				nodesToVisit.push_back(endNodeRecord);
			}
		}
		nodesToVisit.remove(currentNode);
		visitedNodes.push_back(currentNode);
	}

	if (currentNode->mpNode == pTo)
	{
		while (currentNode->mpNode != pFrom)
		{
			mPath.add(currentNode->mpNode);
			currentNode = findNodeRecord(visitedNodes, currentNode->mpConnection->getFromNode());
		}
		mPath.reverse();
	}

	for (std::list<NodeRecord*>::const_iterator iterator = nodesToVisit.begin(), end = nodesToVisit.end(); iterator != end; ++iterator) //Clear lists
	{
		delete *(iterator);
	}

	for (std::list<NodeRecord*>::const_iterator iterator = visitedNodes.begin(), end = visitedNodes.end(); iterator != end; ++iterator)
	{
		delete *(iterator);
	}

	return mPath;
}

NodeRecord* AStarPathfinder::getSmallestNode(std::list<NodeRecord*> workingList)
{
	return *std::min_element(workingList.begin(), workingList.end(), [](NodeRecord* const& s1, NodeRecord* const& s2) {return s1->mEstimatedTotalCost < s2->mEstimatedTotalCost; }); //Using lambdas easilly iterate through the list
}

bool AStarPathfinder::containsNode(std::list<NodeRecord*> theList, Node * key)
{
	for (std::list<NodeRecord*>::const_iterator iterator = theList.begin(), end = theList.end(); iterator != end; ++iterator)
	{
		if ((*iterator)->mpNode == key)
		{
			return true;
		}
	}
	return false;
}

NodeRecord * AStarPathfinder::findNodeRecord(std::list<NodeRecord*> theList, Node * key)
{
	for (std::list<NodeRecord*>::const_iterator iterator = theList.begin(), end = theList.end(); iterator != end; ++iterator)
	{
		if ((*iterator)->mpNode == key)
		{
			return *iterator;
		}
	}
	return nullptr;
}

