#pragma once

#include <glm.hpp>
#include <Trackable.h>
#include <vector>

typedef int NODE_ID;
const NODE_ID BAD_NODE_ID = -1;

class Graph;

class Node : public Trackable
{
public:
	Node();
	Node(const NODE_ID& id, const glm::vec3& pos);
	Node(const NODE_ID& id, float x, float y, float z);
	~Node();

	const NODE_ID& getId() const;

	float	getX() const;
	float	getY() const;
	float	getZ() const;

	glm::vec3	getPosition() const;

private:
	const NODE_ID	mId;
	const float	mX;
	const float	mY;
	const float mZ;
};