#pragma once

#include <vector>
#include <Trackable.h>
#include "NodeRecord.h"
class Node;

class Path :public Trackable
{
public:
	Path();
	~Path();

	Node* peekNode(int index) const;
	Node* peekNextNode() const;
	Node* getAndRemoveNextNode();
	bool containsNode(Node* pNode) const;
	int getNumNodes() const { return mNodes.size(); };

	void addNode(Node* pNode);
	void clear();//remove all nodes
	void reversePath();
private:
	std::vector<Node*> mNodes;

};