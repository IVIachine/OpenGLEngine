#ifndef NAVIGATION_MESH_H
#define NAVIGATION_MESH_H

#include <map>
#include <Trackable.h>
#include "HalfEdge.h"
#include "Vertex.h"
#include <vector>
#include <cmath>
#include <detail\type_vec3.hpp>
struct EdgeTemp
{
	glm::vec3 mFirst, mSecond;
};

struct FaceTemp {
	std::vector<EdgeTemp> edges;

	friend bool operator==(FaceTemp lhs, FaceTemp rhs)
	{
		if (lhs.edges.size() != rhs.edges.size())
		{
			return false;
		}
		for (size_t i = 0; i < lhs.edges.size(); i++)
		{
			if (lhs.edges[i].mFirst != rhs.edges[i].mFirst || lhs.edges[i].mSecond != rhs.edges[i].mSecond)
				return false;
		}
		return true;
	}
};



class NavigationMesh :public Trackable
{
private:
	
	std::vector<EdgeTemp> mEdges;
	std::vector<glm::vec3> mVerts;
public:
	NavigationMesh();
	~NavigationMesh();

	void constructMesh(std::vector<glm::vec3> vertices, std::vector<size_t> indices, size_t faceCount);
	void splitTriangles(std::vector<glm::vec3>& vertices, std::vector<size_t> indices, std::vector<EdgeTemp>& edges, size_t faceCount);

	bool containsVertice(std::vector<glm::vec3> vertices, glm::vec3 key);
	bool reverseExists(std::vector<EdgeTemp> edges, EdgeTemp key);

	void gatherEdges(std::vector<EdgeTemp>& edges, std::vector<FaceTemp>& faces, std::vector<glm::vec3>& vertices, std::vector<size_t> indices, size_t faceCount);

	glm::vec3 getIntersection(EdgeTemp one, EdgeTemp two);
	std::vector<FaceTemp> getEdgeFaces(std::vector<FaceTemp>& faces, EdgeTemp key);
	float norm2(glm::vec3 v);

};
#endif
