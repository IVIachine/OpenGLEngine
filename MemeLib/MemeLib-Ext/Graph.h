#ifndef _GRAPH_H_
#define _GRAPH_H_

#include <vector>
#include <map>
#include <Trackable.h>
#include "Node.h"

class Connection;

typedef std::vector<Node*> NodeList;
typedef std::vector<Connection*> ConnectionList;
typedef std::map<NODE_ID, ConnectionList> ConnectionMap;

class Graph : public Trackable
{
public:
	Graph();
	virtual ~Graph();

	virtual void beginStep();

	void			clear();

	Node*			getNode(size_t index);
	Node*			getNode(Vec3 pos);
	NodeList		getNodes() const;
	size_t			size() const;

	ConnectionList	getConnections(const Node& pSource);
	ConnectionList	getConnections(const NODE_ID& sourceID);
	ConnectionList	getAllConnections() { return m_connectionList; };

	Connection*		getConnection(const Node& pSource, const Node& pTarget);
	Connection*		getConnection(const NODE_ID& sourceID, const NODE_ID& targetID);

	NodeList		getNeighbors(const Node& pSource, bool diagonals);
	NodeList		getNeighbors(const NODE_ID& sourceID, bool diagonals);

	Node*			operator[](size_t index);

protected:
	NodeList		m_nodeList;
	ConnectionList	m_connectionList;
	ConnectionMap	m_connectionMap;
};

#endif // !_GRAPH_H_H
