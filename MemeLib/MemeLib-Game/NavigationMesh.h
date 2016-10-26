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
#include "Vector3.h"
#include "Vector2.h"
#include <glm.hpp>

const static float TOLERANCE = 0.00005f;

struct Edge
{
	_vec3 first, second;

	Edge() : first({ 0.f, 0.f, 0.f }), second({ 0.f, 0.f, 0.f }) {};
	Edge(_vec3 a, _vec3 b) : first(a), second(b) { };

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
	std::vector<_vec3>	m_vertices;

	

public:
	NavigationMesh();
	~NavigationMesh();

	void constructMesh(Mesh* mesh);
	void splitTriangles(std::vector<_vec3>& vertices, std::vector<size_t> indices, std::vector<Edge>& edges, size_t faceCount);

	bool containsVertice(std::vector<_vec3> vertices, _vec3 key);
	bool reverseExists(std::vector<Edge> edges, Edge key);

	void gatherEdges(std::vector<Edge>& edges, std::vector<Face>& faces, std::vector<_vec3>& vertices, std::vector<size_t> indices, size_t faceCount);

	std::vector<Edge> getKnownConnections(_vec3 key);
	Node* getOtherNode(Edge tmp, Node* key);
	std::vector<Face> getEdgeFaces(std::vector<Face>& faces, Edge key);
	float norm2(_vec3 v) const;

	size_t	vertCount() const { return m_vertices.size(); };
	size_t	edgeCount() const { return m_edges.size(); };
	Edge*	getEdge(size_t index) { return &m_edges[index]; };

	bool getIntersection(Edge one, Edge two, _vec3& ip) const;
	bool getIntersection(Edge edge, _vec3 ip) const;

	std::vector<Edge> getEdges() const
	{
		return m_edges;
	};

	std::vector<_vec3> getVerts() const
	{
		return m_vertices;
	};
};
#endif
