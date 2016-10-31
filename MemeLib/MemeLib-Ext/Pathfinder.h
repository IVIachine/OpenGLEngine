#ifndef _PATHFINDER_H_
#define _PATHFINDER_H_

#include <vector>
#include <Trackable.h>
#include "Path.h"

class Graph;
class Node;

class Pathfinder :public Trackable
{
public:
	Pathfinder(Graph* pGraph);
	virtual ~Pathfinder();

	virtual const Path& findPath(Node* pFrom, Node* pTo) = 0;

	Path getPath() { return mPath; };

protected:
	Graph*	mpGraph;
	Path	mPath;
};

#endif // !_PATHFINDER_H_
