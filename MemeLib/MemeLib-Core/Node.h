#pragma once

#include <Trackable.h>
#include <glm.hpp>

const int BAD_NODE_ID = -1;
#define NODE_ID int

class Node :public Trackable
{
public:
	Node(const NODE_ID& id, glm::vec3 pos);
	Node();
	~Node();

	const NODE_ID& getId() const { return mId; };
	glm::vec3 getPos() { return mPos; };
private:
	const NODE_ID mId;
	glm::vec3 mPos;
};