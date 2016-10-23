#pragma once

#include <vector>
#include <Trackable.h>
#include "Path.h"

class Graph;
class Node;
class GraphicsBuffer;
class Grid;

#define VISUALIZE_PATH 1

class Pathfinder :public Trackable
{
public:
	Pathfinder(Graph* pGraph);
	virtual ~Pathfinder();
	Path getPath() { return mPath; };
	virtual const Path& findPath(Node* pFrom, Node* pTo) = 0;
protected:
	Graph* mpGraph;
	Path mPath;  //cached version of the calculated path

};