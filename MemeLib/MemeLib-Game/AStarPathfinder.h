#ifndef _ASTAR_PATHFINDER_H_
#define _ASTAR_PATHFINDER_H_

#include <list>
#include "Pathfinder.h"

class Path;
class Graph;

#define UNWALKABLE FLT_MAX
#define DIAGONAL 0.1f

struct AStarOptions
{
	bool	enableHeuristic;
	bool	enableDiagonals;
	size_t	maxDistance;

	AStarOptions()
	{
		enableDiagonals = true;
		enableHeuristic = true;
		maxDistance = 0;
	};
};

class AStarPathfinder : public Pathfinder
{
public:
	AStarPathfinder(Graph* pGraph);
	~AStarPathfinder();

	const Path& findPath(Node* pSource, Node* pTarget) override;

	AStarOptions* getOptions() { return &m_options; }

private:
	AStarOptions m_options;

	float	costToEnterNode(Node* pSource, Node* pTarget);
};

#endif // !_ASTAR_PATHFINDER_H_