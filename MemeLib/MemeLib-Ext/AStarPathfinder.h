#ifndef _ASTAR_PATHFINDER_H_
#define _ASTAR_PATHFINDER_H_

#include <list>
#include <map>
#include "Pathfinder.h"
#include "Vector3.h"

class Path;
class Node;
class Graph;

#define UNWALKABLE FLT_MAX
#define DIAGONAL 0.1f

enum AStarState
{
	Idle = 0,
	Working,
	Done,
	NoPathFound,
	PathFound
};

struct AStarOptions
{
	bool	enableDiagonals;
	bool	enableHeuristic;
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
	
	void		setSource(Node* pSource);
	void		setTarget(Node* pTarget);

	AStarState	getState() const;
	void		setState(AStarState value);

	void		beginStep();
	void		step();
	AStarState	endStep();

private:
	AStarOptions m_options;

	float	costToEnterNode(Node* pSource, Node* pTarget);

	AStarState m_state = Idle;
	Node* mp_source;
	Node* mp_target;
	std::map<Node*, float> m_distMap;
	std::map<Node*, Node*> m_prevMap;
	std::list<Node*> m_unvisitedList;

};

#endif // !_ASTAR_PATHFINDER_H_