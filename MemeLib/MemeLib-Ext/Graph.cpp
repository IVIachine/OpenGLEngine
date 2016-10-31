#include "Graph.h"
#include "Connection.h"

Graph::Graph()
{
}

Graph::~Graph()
{
	for (unsigned int i = 0; i<m_nodeList.size(); i++)
	{
		delete m_nodeList[i];
	}

	for (unsigned int i = 0; i<m_connectionList.size(); i++)
	{
		delete m_connectionList[i];
	}
}


void Graph::beginStep()
{
}


Node* Graph::getNode(size_t index)
{
	if (index < m_nodeList.size())
	{
		return m_nodeList[index];
	}

	return NULL;
}

Node * Graph::getNode(Vec3 pos)
{
	for (size_t i = 0; i < m_nodeList.size(); i++)
	{
		if (m_nodeList[i]->getPosition() == pos)
		{
			return m_nodeList[i];
		}
	}
	return NULL;
}

NodeList Graph::getNodes() const
{
	return m_nodeList;
}

size_t Graph::size() const
{
	return m_nodeList.size();
}


ConnectionList Graph::getConnections(const Node& pSource)
{
	return getConnections(pSource.getId());
}

ConnectionList Graph::getConnections(const NODE_ID& sourceID)
{
	static ConnectionList sEmpty;

	ConnectionMap::iterator iter = m_connectionMap.find(sourceID);

	if (iter == m_connectionMap.end())
	{
		return sEmpty;
	}
	else
	{
		return iter->second;
	}
}


Connection* Graph::getConnection(const Node& pSource, const Node& pTarget)
{
	return getConnection(pSource.getId(), pTarget.getId());
}

Connection* Graph::getConnection(const NODE_ID& sourceID, const NODE_ID& targetID)
{
	ConnectionList connections = getConnections(sourceID);

	for (Connection* c : connections)
	{
		if (c->getTarget()->getId() == targetID)
		{
			return c;
		}
	}

	return NULL;
}


NodeList Graph::getNeighbors(const Node& pSource, bool diagonals)
{
	return getNeighbors(pSource.getId(), diagonals);
}

NodeList Graph::getNeighbors(const NODE_ID& sourceID, bool diagonals)
{
	NodeList		neighbors;
	ConnectionList	connections = getConnections(sourceID);

	for (size_t i = 0; i < connections.size(); i++)
	{
		Connection* pConnection = connections[i];

		if (!pConnection->isDiagonal() || diagonals)
		{
			Node* pTarget = pConnection->getTarget();

			neighbors.push_back(pTarget);
		}
	}

	return neighbors;
}


Node* Graph::operator[](size_t index)
{
	return getNode(index);
}