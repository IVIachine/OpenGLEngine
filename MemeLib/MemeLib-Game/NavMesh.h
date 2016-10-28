#ifndef NAVIGATION_MESH_H
#define NAVIGATION_MESH_H

#include <map>
#include <Trackable.h>
#include "HalfEdge.h"
#include "Vertex.h"
#include <vector>
#include <cmath>
#include "Graph.h"
#include "Mesh.h"
#include <detail\type_vec3.hpp>

const static float TOLERANCE = 0.00005f;

struct Edge
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


class NavMesh : public Graph
{
public:
	NavMesh();
	~NavMesh();

	void constructMesh(Mesh* mesh);
	void splitTriangles(std::vector<Vec3>& vertices, std::vector<size_t> indices, std::vector<Edge>& edges, size_t faceCount);

	bool containsVertice(std::vector<Vec3> vertices, Vec3 key);
	bool reverseExists(std::vector<Edge> edges, Edge key);

	void gatherEdges(std::vector<Edge>& edges, std::vector<Face>& faces, std::vector<Vec3>& vertices, std::vector<size_t> indices, size_t faceCount);

	std::vector<Edge> getKnownConnections(Vec3 key);
	Node* getOtherNode(Edge tmp, Node* key);
	std::vector<Face> getEdgeFaces(std::vector<Face>& faces, Edge key);
	float norm2(Vec3 v) const;

	size_t	vertCount() const { return m_vertices.size(); };
	size_t	edgeCount() const { return m_edges.size(); };
	Edge*	getEdge(size_t index) { return &m_edges[index]; };

	bool getIntersection(Edge one, Edge two, Vec3& ip) const;
	bool getIntersection(Edge edge, Vec3 ip) const;

	std::vector<Edge> getEdges() const
	{
		return m_edges;
	};

	std::vector<Vec3> getVerts() const
	{
		return m_vertices;
	};

private:
	std::vector<Edge>	m_edges;
	std::vector<Vec3>	m_vertices;
};
#endif
