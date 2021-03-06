#include "AStarPathfinder.h"
#include <cassert>
#include "Path.h"
#include "Connection.h"
#include "Graph.h"
#include "Game.h"
#include <PerformanceTracker.h>
#include <list>
#include <vector>
#include <algorithm>
#include <map>
#include "Vector3.h"

AStarPathfinder::AStarPathfinder(Graph* pGraph)
	: Pathfinder(dynamic_cast<Graph*>(pGraph))
{
}

AStarPathfinder::~AStarPathfinder()
{

}


const Path& AStarPathfinder::findPath(Node* pSource, Node* pTarget)
{
	// Clear path
	mPath.clear();

	std::map<Node*, float> distMap;
	std::map<Node*, Node*> prevMap;
	std::list<Node*> unvisitedList;

	distMap[pSource] = 0.0f;
	prevMap[pSource] = NULL;

	// Get all nodes
	for (Node* node : mpGraph->getNodes())
	{
		if (node != pSource)
		{
			distMap[node] = UNWALKABLE;
			prevMap[node] = NULL;
		}

		unvisitedList.push_back(node);
	}

	while (unvisitedList.size() > 0)
	{
		// Get unvisited with smallest distance
		Node* unvisitedNode = NULL;
		for (Node* possible : unvisitedList)
		{
			if (!unvisitedNode || distMap[possible] < distMap[unvisitedNode])
			{
				unvisitedNode = possible;
			}
		}

		// At target
		if (unvisitedNode == pTarget)
		{
			break;
		}

		// Mark the node as 'visited'
		unvisitedList.remove(unvisitedNode);

		// Get neighbor nodes
		std::vector<Node*> neighborList =
			mpGraph->getNeighbors(*unvisitedNode, m_options.enableDiagonals);

		// Check for alternate path
		for (Node* neighborNode : neighborList)
		{
			// Get cost
			float costToEnter = costToEnterNode(
				unvisitedNode,
				neighborNode);

			float altDist = distMap[unvisitedNode] + costToEnter;

			if (altDist < distMap[neighborNode])
			{
				distMap[neighborNode] = altDist;
				prevMap[neighborNode] = unvisitedNode;
			}
		}
	}

	// No path found
	if (prevMap[pTarget] == NULL)
	{
		return mPath;
	}

	// Build path
	Node* currentNode = pTarget;
	while (currentNode != NULL)
	{
		mPath.add(currentNode);
		currentNode = prevMap[currentNode];
	}

	// Reverse the path
	mPath.reverse();

	// Resize the path
	if (m_options.maxDistance > 0)
	{
		mPath.resize(m_options.maxDistance);
	}

	return mPath;
}

float AStarPathfinder::costToEnterNode(Node* pSource, Node* pTarget)
{
	// Get connection
	Connection* pConnection = mpGraph->getConnection(*pSource, *pTarget);

	// No connection or unwalkable
	if (!pConnection || !pConnection->isWalkable())
	{
		return UNWALKABLE;
	}

	// Get move cost
	float cost = 1.0f;

	// Use heuristic
	if (m_options.enableHeuristic)	
	{
		cost = pConnection->moveCost();

		if (pConnection->isDiagonal())
		{
			cost += DIAGONAL;
		}
	}

	return cost;
}



void AStarPathfinder::setSource(Node* pSource)
{
	mp_source = pSource;
}

void AStarPathfinder::setTarget(Node* pTarget)
{
	mp_target = pTarget;
}


AStarState AStarPathfinder::getState() const
{
	return m_state;
}

void AStarPathfinder::setState(AStarState value)
{
	m_state = value;
}


void AStarPathfinder::beginStep()
{
	assert(mp_source != NULL);
	assert(mp_target != NULL);

	// Set state
	setState(Working);

	// Clear path
	mPath.clear();
	m_distMap.clear();
	m_prevMap.clear();
	m_unvisitedList.clear();

	m_distMap[mp_source] = 0.0f;
	m_prevMap[mp_source] = NULL;

	// Get all nodes
	for (Node* node : mpGraph->getNodes())
	{
		if (node != mp_source)
		{
			m_distMap[node] = UNWALKABLE;
			m_prevMap[node] = NULL;
		}

		m_unvisitedList.push_back(node);
	}
}

void AStarPathfinder::step()
{
	if (m_state != Working)
	{
		return;
	}

	if (m_unvisitedList.size() > 0)
	{
		// Get unvisited with smallest distance
		Node* unvisitedNode = NULL;
		for (Node* possible : m_unvisitedList)
		{
			if (!unvisitedNode || m_distMap[possible] < m_distMap[unvisitedNode])
			{
				unvisitedNode = possible;
			}
		}

		// At target
		if (unvisitedNode == mp_target)
		{
			setState(Done);
			return;
		}

		// Mark the node as 'visited'
		m_unvisitedList.remove(unvisitedNode);

		// Get neighbor nodes
		std::vector<Node*> neighborList =
			mpGraph->getNeighbors(*unvisitedNode, m_options.enableDiagonals);

		// Check for alternate path
		for (Node* neighborNode : neighborList)
		{
			// Get cost
			float costToEnter = costToEnterNode(
				unvisitedNode,
				neighborNode);

			float altDist = m_distMap[unvisitedNode] + costToEnter;

			if (altDist < m_distMap[neighborNode])
			{
				m_distMap[neighborNode] = altDist;
				m_prevMap[neighborNode] = unvisitedNode;
			}
		}
	}
}

AStarState AStarPathfinder::endStep()
{
	if (m_prevMap[mp_target] == NULL)
	{
		// No path found
		setState(NoPathFound);
	}
	else
	{
		// Path found
		setState(PathFound);

		// Build path
		Node* currentNode = mp_target;
		while (currentNode != NULL)
		{
			mPath.add(currentNode);
			currentNode = m_prevMap[currentNode];
		}

		// Reverse the path
		mPath.reverse();
		// Resize the path
		if (m_options.maxDistance > 0)
		{
			mPath.resize(m_options.maxDistance);
		}
	}
	return m_state;
}