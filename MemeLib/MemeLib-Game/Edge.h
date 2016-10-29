#ifndef _EDGE_H_
#define _EDGE_H_

#include "Vector3.h"

struct Edge : public Trackable
{
	Vec3 first, second;

	Edge() : first(Vec3_Zero), second(Vec3_Zero) {};
	Edge(Vec3 a, Vec3 b) : first(a), second(b) { };

	friend bool operator == (const Edge& lhs, const Edge& rhs)
	{
		return lhs.first == rhs.first && lhs.second == rhs.second;
	}

	friend bool operator != (const Edge& lhs, const Edge& rhs)
	{
		return lhs.first != rhs.first || lhs.second != rhs.second;
	}

	friend bool operator < (const Edge& lhs, const Edge& rhs)
	{
		return
			lhs.first.x < rhs.first.x &&
			lhs.first.y < rhs.first.y &&
			lhs.first.z < rhs.first.z &&

			lhs.second.x < rhs.second.x &&
			lhs.second.y < rhs.second.y &&
			lhs.second.z < rhs.second.z;
	}
};

#endif // !_EDGE_H_
