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

typedef std::vector<Edge> EdgeList;
typedef std::vector<Face> FaceList;
typedef std::vector<Vec3> VertList;

class NavMesh : public Graph
{
public:
	NavMesh();
	~NavMesh();

	void	constructMesh(Mesh* mesh);
	void	gatherEdges(EdgeList& edges, FaceList& faces, VertList& vertices, std::vector<size_t> indices, size_t faceCount);
	void	splitTriangles(VertList& vertices, std::vector<size_t> indices, EdgeList& edges, size_t faceCount);

	bool	containsVertice(std::vector<Vec3> vertices, Vec3 key);
	bool	getIntersection(Edge one, Edge two, Vec3& ip) const;
	bool	getIntersection(Edge edge, Vec3 ip) const;
	bool	reverseExists(std::vector<Edge> edges, Edge key);

	EdgeList	getEdges() const;
	EdgeList	getKnownConnections(Vec3 key);
	FaceList	getEdgeFaces(std::vector<Face>& faces, Edge key);
	VertList	getVerts() const;

	Edge*		getEdge(size_t index);
	Node*		getOtherNode(Edge tmp, Node* key);

	size_t		vertCount() const;
	size_t		edgeCount() const;

	Node*	findNearestNode(const Vec3& position);

private:
	std::vector<Edge>	m_edges;
	std::vector<Vec3>	m_vertices;

	inline float norm2(Vec3 v) const
	{
		return v.x * v.x + v.y * v.y + v.z * v.z;
	};
};
#endif