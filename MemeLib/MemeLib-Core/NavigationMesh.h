#ifndef NAVIGATION_MESH_H
#define NAVIGATION_MESH_H

#include <map>
#include <Trackable.h>
#include "HalfEdge.h"
#include "Vertex.h"
#include <vector>
#include <cmath>
#include "Graph.h"
#include <detail\type_vec3.hpp>

struct Edge
{
	glm::vec3 first, second;

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

struct FaceTemp {
	std::vector<Edge> edges;

	friend bool operator==(FaceTemp lhs, FaceTemp rhs)
	{
		if (lhs.edges.size() != rhs.edges.size())
		{
			return false;
		}
		for (size_t i = 0; i < lhs.edges.size(); i++)
		{
			if (lhs.edges[i].first != rhs.edges[i].first || lhs.edges[i].second != rhs.edges[i].second)
				return false;
		}
		return true;
	}
};


class NavigationMesh :public Graph
{
private:
	std::vector<Edge> mEdges;
	std::vector<glm::vec3> mVerts;

	

public:
	NavigationMesh();
	~NavigationMesh();

	void constructMesh(std::vector<glm::vec3> vertices, std::vector<size_t> indices, size_t faceCount);
	void splitTriangles(std::vector<glm::vec3>& vertices, std::vector<size_t> indices, std::vector<Edge>& edges, size_t faceCount);

	bool containsVertice(std::vector<glm::vec3> vertices, glm::vec3 key);
	bool reverseExists(std::vector<Edge> edges, Edge key);

	void gatherEdges(std::vector<Edge>& edges, std::vector<FaceTemp>& faces, std::vector<glm::vec3>& vertices, std::vector<size_t> indices, size_t faceCount);

	std::vector<Edge> getKnownConnections(glm::vec3 key);
	Node* getOtherNode(Edge tmp, Node* key);
	bool getIntersection(Edge one, Edge two, glm::vec3& ip);
	std::vector<FaceTemp> getEdgeFaces(std::vector<FaceTemp>& faces, Edge key);
	float norm2(glm::vec3 v);

	size_t vertCount() const { return mVerts.size(); };

	size_t edgeCount() const { return mEdges.size(); };
	Edge* getEdge(size_t index) { return &mEdges[index]; };
};
#endif
