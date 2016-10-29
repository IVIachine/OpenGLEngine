#ifndef _NAV_MESH_H_
#define _NAV_MESH_H_

#include <map>
#include <Trackable.h>
#include "HalfEdge.h"
#include "Vertex.h"
#include <vector>
#include <cmath>
#include "Graph.h"
#include "Mesh.h"
#include "Face.h"

const static float TOLERANCE = 0.00005f;

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
