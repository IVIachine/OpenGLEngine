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

typedef glm::vec3 Point;

struct Edge
{
	Point first, second;

	Edge() : first({ 0.f, 0.f, 0.f }), second({ 0.f, 0.f, 0.f }) {};
	Edge(Point a, Point b) : first(a), second(b) { };

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

struct Face
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
			if (lhs.edges[i].first != rhs.edges[i].first || lhs.edges[i].second != rhs.edges[i].second)
				return false;
		}
		return true;
	}
};


class NavigationMesh :public Graph
{
private:
	std::vector<Edge>		m_edges;
	std::vector<Point>	m_vertices;

	

public:
	NavigationMesh();
	~NavigationMesh();

	void constructMesh(std::vector<Point> vertices, std::vector<size_t> indices, size_t faceCount);
	void splitTriangles(std::vector<Point>& vertices, std::vector<size_t> indices, std::vector<Edge>& edges, size_t faceCount);

	bool containsVertice(std::vector<Point> vertices, Point key);
	bool reverseExists(std::vector<Edge> edges, Edge key);

	void gatherEdges(std::vector<Edge>& edges, std::vector<Face>& faces, std::vector<Point>& vertices, std::vector<size_t> indices, size_t faceCount);

	std::vector<Edge> getKnownConnections(Point key);
	Node* getOtherNode(Edge tmp, Node* key);
	std::vector<Face> getEdgeFaces(std::vector<Face>& faces, Edge key);
	float norm2(Point v);

	size_t	vertCount() const { return m_vertices.size(); };
	size_t	edgeCount() const { return m_edges.size(); };
	Edge*	getEdge(size_t index) { return &m_edges[index]; };

	bool getIntersection(Edge one, Edge two, Point& ip);
	bool getIntersection(Edge edge, Point ip);
};
#endif
