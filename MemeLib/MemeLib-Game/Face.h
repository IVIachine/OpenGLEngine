#ifndef _FACE_H_
#define _FACE_H_

#include "Edge.h"
#include <vector>

struct Face : public Trackable
{
	std::vector<Edge> edges;

	friend bool operator==(Face lhs, Face rhs)
	{
		if (lhs.edges.size() != rhs.edges.size())
		{
			return false;
		}

		for (size_t i = 0; i < lhs.edges.size(); i++)
		{
			if ((lhs.edges[i].first != rhs.edges[i].first) ||
				(lhs.edges[i].second != rhs.edges[i].second))
			{
				return false;
			}
		}
		return true;
	}
};

#endif // !_FACE_H_
