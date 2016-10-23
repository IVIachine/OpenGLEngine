#include <list>
#include "Heuristic.h"
#include "Pathfinder.h"
class Path;
class Graph;
class GraphicsBuffer;
class Grid;

class AStarPathfinder :public Pathfinder 
{
public:
	AStarPathfinder(Graph* pGraph);
	~AStarPathfinder();

	const Path& findPath(Node* pFrom, Node* pTo);

	NodeRecord* getSmallestNode(std::list<NodeRecord*> workingList);
	bool containsNode(std::list<NodeRecord*> theList, Node * key);
	NodeRecord* findNodeRecord(std::list<NodeRecord*> theList, Node* key);
};

