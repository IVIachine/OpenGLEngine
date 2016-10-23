#pragma once

#include <glm.hpp>
#include <Trackable.h>
<<<<<<< HEAD
#include <vector>
=======
#include <glm.hpp>
>>>>>>> 58c450c58599be32e2e224583775b33a58d99793

typedef int NODE_ID;
const NODE_ID BAD_NODE_ID = -1;

class Graph;

class Node : public Trackable
{
public:
<<<<<<< HEAD
=======
	Node(const NODE_ID& id, glm::vec3 pos);
>>>>>>> 58c450c58599be32e2e224583775b33a58d99793
	Node();
	Node(const NODE_ID& id, const glm::vec3& pos);
	Node(const NODE_ID& id, float x, float y, float z);
	~Node();

<<<<<<< HEAD
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
=======
	const NODE_ID& getId() const { return mId; };
	glm::vec3 getPos() { return mPos; };
private:
	const NODE_ID mId;
	glm::vec3 mPos;
>>>>>>> 58c450c58599be32e2e224583775b33a58d99793
};