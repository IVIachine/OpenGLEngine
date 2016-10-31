#include "NavMesh.h"
#include <algorithm>
#include "Connection.h"
#include "Vector3.h"

NavMesh::NavMesh()
{
}

NavMesh::~NavMesh()
{
}


void NavMesh::constructMesh(Mesh* mesh)
{
	std::vector<Edge> edges;
	std::vector<Vec3> verts = mesh->getVerts();
	splitTriangles(verts, mesh->getIndices(), edges, mesh->getCount()); //Split the intersections into multiple edges for accuracy
	m_vertices = verts;
	m_edges = edges;

	m_nodeList.resize(m_vertices.size(), NULL);

	for (size_t i = 0; i < m_vertices.size(); i++)
	{
		Node* pNode = new Node(i, m_vertices[i]);
		m_nodeList[i] = pNode;
	}


	for (size_t i = 0; i < m_vertices.size(); i++)
	{
		Node* pSource = m_nodeList[i];
		ConnectionList connections;
		std::vector<Edge> knownConnections = getKnownConnections(pSource->getPosition());

		for (size_t j = 0; j < knownConnections.size(); j++)
		{
			Node* pTarget = getOtherNode(knownConnections[j], pSource);

			float	moveCost = Vector3::distance(pSource->getPosition(), pTarget->getPosition());
			bool	isWalkable = true;

			if (isWalkable)
			{
				Connection* pConnection = new Connection(
					pSource, 
					pTarget, 
					moveCost,
					isWalkable);

				m_connectionList.push_back(pConnection);
				connections.push_back(pConnection);
			}
		}

		m_connectionMap[i] = connections;
	}
}

void NavMesh::gatherEdges(
	EdgeList& edges, FaceList& faces, VertList& vertices, std::vector<size_t> indices, size_t faceCount)
{
	for (size_t i = 0; i < faceCount; i += 3)
	{
		Edge tmp, tmp2, tmp3;
		tmp.first = vertices[indices[i]];
		tmp.second = vertices[indices[i + 1]];

		tmp2.first = vertices[indices[i + 1]];
		tmp2.second = vertices[indices[i + 2]];

		tmp3.first = vertices[indices[i + 2]];
		tmp3.second = vertices[indices[i]];

		if (!reverseExists(edges, tmp))
			edges.push_back(tmp);

		if (!reverseExists(edges, tmp2))
			edges.push_back(tmp2);

		if (!reverseExists(edges, tmp3))
			edges.push_back(tmp3);

		Face faceTemp;
		faceTemp.edges.push_back(tmp);
		faceTemp.edges.push_back(tmp2);
		faceTemp.edges.push_back(tmp3);
		faces.push_back(faceTemp);
	}
}

void NavMesh::splitTriangles(
	VertList& vertices, std::vector<size_t> indices, EdgeList& edges, size_t faceCount)
{
	std::vector<Face> faces;
	gatherEdges(edges, faces, vertices, indices, faceCount);

	size_t size = edges.size();
	for (size_t i = 0; i < size; i++)
	{
		for (size_t j = 0; j < size; j++)
		{
			// ignore if same edge
			if (i == j)
			{
				continue;
			}

			// get intersection point
			Vec3 ip;
			if (getIntersection(edges[i], edges[j], ip))
			{
				// add vertice if not exists
				if (std::find(vertices.begin(), vertices.end(), ip) == vertices.end())
				{
					vertices.push_back(ip);
				}

				// beginning or end of edges[i]
				if (ip != edges[i].first && ip != edges[i].second)
				{
					Edge a{ edges[i].first, ip };
					Edge b{ ip, edges[i].second };

					edges[i] = a;
					edges.push_back(b);
				}
			}
		}
	}

	// cleanup overlooked edges
	size = edges.size();
	for (size_t i = 0; i < size; i++)
	{
		for (size_t j = 0; j < vertices.size(); j++)
		{
			Vec3 ip = vertices[j];

			if (getIntersection(edges[i], ip))
			{
				Edge a{ edges[i].first, ip };
				Edge b{ ip, edges[i].second };

				if (std::find(edges.begin(), edges.end(), a) == edges.end())
				{
					if (std::find(edges.begin(), edges.end(), b) == edges.end())
					{
						edges[i] = a;
						edges.push_back(b);
					}
				}
			}
		}
	}
}


bool NavMesh::containsVertice(std::vector<Vec3> vertices, Vec3 key)
{
	for (size_t i = 0; i < vertices.size(); i++)
	{
		if (vertices[i] == key)
		{
			return true;
		}
	}
	return false;
}

bool NavMesh::getIntersection(Edge one, Edge two, Vec3& ip) const
{
	//CITE: http://stackoverflow.com/questions/2316490/the-algorithm-to-find-the-point-of-intersection-of-two-3d-line-segment

	if (one.first == two.first || one.first == two.second || one.second == two.first || one.first == two.second) //edges share a point
	{
		false;
	}

	Vec3 da = one.second - one.first;
	Vec3 db = two.second - two.first;
	Vec3 dc = two.first - one.first;

	if (glm::dot(dc, glm::cross(da, db)) != 0.f)
	{
		return false;
	}

	float s = glm::dot(glm::cross(dc, db), glm::cross(da, db)) / norm2(glm::cross(da, db));

	if (s >= 0.0f && s <= 1.0f)
	{
		ip = one.first + da * Vec3(s, s, s);

		return true;
	}

	return false;
}

bool NavMesh::getIntersection(Edge edge, Vec3 point) const
{
	Vec3 a = edge.first;
	Vec3 b = edge.second;
	Vec3 c = point;

	float dac = Vector3::distance(a, c);
	float dbc = Vector3::distance(b, c);
	float dab = Vector3::distance(a, b);
	float sum = dac + dbc;

	if (sum == dab)
	{
		return true;
	}
	else if (sum >= dab - TOLERANCE && sum < dab + TOLERANCE)
	{
		return true;
	}

	return false;
}

bool NavMesh::reverseExists(std::vector<Edge> edges, Edge key)
{
	for (size_t i = 0; i < edges.size(); i++)
	{
		if ((edges[i].first == key.second && edges[i].second == key.first) || (edges[i].first == key.first && edges[i].second == key.second))
		{
			return true;
		}
	}
	return false;
}


EdgeList NavMesh::getEdges() const
{
	return m_edges;
}

EdgeList NavMesh::getKnownConnections(Vec3 key)
{
	std::vector<Edge> result;
	for (size_t i = 0; i < m_edges.size(); i++)
	{
		if (m_edges[i].first == key || m_edges[i].second == key)
			result.push_back(m_edges[i]);
	}
	return result;
}

FaceList NavMesh::getEdgeFaces(std::vector<Face>& faces, Edge key)
{
	std::vector<Face> faceResult;
	bool exists = false;
	for (size_t i = 0; i < faces.size(); i++)
	{
		for (size_t j = 0; j < faces[i].edges.size(); j++)
		{
			if ((faces[i].edges[j].first == key.first && faces[i].edges[j].second == key.second) ||
				(faces[i].edges[j].first.x == key.second.x && faces[i].edges[j].first.z == key.second.z))
			{
				exists = false;

				for (size_t k = 0; k < faceResult.size(); k++)
				{
					if (faces[i].edges.size() != faceResult[k].edges.size())
						break;

					for (size_t f = 0; f < faces[i].edges.size(); f++)
					{
						if ((faces[i].edges[f].first == faceResult[k].edges[f].first && faces[i].edges[f].second == faceResult[k].edges[f].second) ||
							(faces[i].edges[f].second == faceResult[k].edges[f].first && faces[i].edges[f].first == faceResult[k].edges[f].second))
						{
							exists = true;
						}
					}
				}

				if (!exists)
					faceResult.push_back(faces[i]);
			}
		}
	}
	return faceResult;
}

VertList NavMesh::getVerts() const
{
	return m_vertices;
}


Edge * NavMesh::getEdge(size_t index)
{
	return &m_edges[index];
}

Node * NavMesh::getOtherNode(Edge tmp, Node* key)
{
	if (key->getPosition() == tmp.first)
	{
		return getNode(tmp.second);
	}
	else if (key->getPosition() == tmp.second)
	{
		return getNode(tmp.first);
	}
	return NULL;
}

size_t NavMesh::vertCount() const
{
	return m_vertices.size();
}

size_t NavMesh::edgeCount() const
{
	return m_edges.size();
}

Node* NavMesh::findNearestNode(const Vec3 & position)
{
	Node* result = NULL;
	float smallest = FLT_MAX;

	for (Node* pNode : m_nodeList)
	{
		float dist = glm::distance(position, pNode->getPosition());

		if (dist < smallest)
		{
			result = pNode;
			smallest = dist;
		}
	}

	return result;
}
