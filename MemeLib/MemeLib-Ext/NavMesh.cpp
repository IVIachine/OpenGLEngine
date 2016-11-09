#include "NavMesh.h"
#include <algorithm>
#include "Connection.h"
#include "Vector3.h"
#include "AStarPathfinder.h"

#include <Timer.h>

NavMesh::NavMesh()
{
}

NavMesh::~NavMesh()
{
}


void NavMesh::constructMesh(Mesh* mesh)
{
	Timer timer;
	timer.start();

	std::vector<Edge> edges;
	std::vector<Vec3> verts = mesh->getVerts();
	splitTriangles(verts, mesh->getIndices(), edges, mesh->getCount()); //Split the intersections into multiple edges for accuracy
	m_vertices = verts;
	m_edges = edges;

	//CONSTRUCT TEMPORARY MESH FOR WIREFRAMES
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

	gatherFaces();

	for (auto* p : m_connectionList)
	{
		p->setWalkable(true);
	}

	timer.stop();
	std::cout << "Elapsed Time: " << timer.getElapsedTime() << "\n";
}

void NavMesh::gatherEdges(
	EdgeList& edges, VertList& vertices, std::vector<size_t> indices, size_t faceCount)
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
	}
}

void NavMesh::splitTriangles(
	VertList& vertices, std::vector<size_t> indices, EdgeList& edges, size_t faceCount)
{
	gatherEdges(edges, vertices, indices, faceCount);

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
			if (getIntersection(edges[i], edges[j], ip) && edges[i] != edges[j])
			{
				// add vertice if not exists
				if (std::find(vertices.begin(), vertices.end(), ip) == vertices.end())
				{
					bool found = false;
					for (auto& p : vertices)
					{
						float dist = Vector3::distance(ip, p);
						if (dist < MIN_DIST)
						{
							found = true;
							break;
						}
					}
					if (!found)
					{
						vertices.push_back(ip);
					}
					else
					{
						continue;
					}
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

	//Check for possible edges between two close points
	for (size_t i = 0; i < vertices.size(); i++)
	{
		for (size_t j = 0; j < vertices.size(); j++)
		{
			if (Vector3::distance(vertices[i], vertices[j]) < MIN_DIST)
			{
				if (!edgeExists(vertices[i], vertices[j], edges))
				{
					edges.push_back(Edge(vertices[i], vertices[j]));
				}
			}
		}
	}
}

void NavMesh::gatherFaces()
{
	bool findingFaces = true;
	while (findingFaces)
	{
		findingFaces = false;
		for (size_t i = 0; i < m_edges.size(); i++)
		{
			removeConnection(m_edges[i]);
			AStarPathfinder pathfinder(this);
			pathfinder.getOptions()->enableHeuristic = false;
			Path foundPath = pathfinder.findPath(getNode(m_edges[i].first), getNode(m_edges[i].second));
			if (foundPath.size() > 2)
			{
				Face newFace;
				EdgeList edges;
				edges.push_back(m_edges[i]);
				for (size_t j = 0; j < foundPath.size() - 1; j++)
				{
					Edge newEdge;
					newEdge.first = foundPath.peek(j)->getPosition();
					newEdge.second = foundPath.peek(j + 1)->getPosition();
					edges.push_back(newEdge);
				}
				newFace.edges = edges;
				if (!faceExists(newFace))
				{
					if (cleanFace(newFace))
					{
						findingFaces = true;
						m_faces.push_back(newFace);
					}
				}
			}
			addConnection(m_edges[i]);
		}
		reduceConnections();
	}
}

void NavMesh::removeConnection(Edge key)
{
	for (size_t i = 0; i < m_connectionList.size(); i++)
	{
		if ((m_connectionList[i]->getSource()->getPosition() == key.first && m_connectionList[i]->getTarget()->getPosition() == key.second) ||
			(m_connectionList[i]->getSource()->getPosition() == key.second && m_connectionList[i]->getTarget()->getPosition() == key.first))
		{
			m_connectionList[i]->setWalkable(false);
		}
	}
}

void NavMesh::addConnection(Edge key)
{
	for (size_t i = 0; i < m_connectionList.size(); i++)
	{
		if ((m_connectionList[i]->getSource()->getPosition() == key.first && m_connectionList[i]->getTarget()->getPosition() == key.second) ||
			(m_connectionList[i]->getSource()->getPosition() == key.second && m_connectionList[i]->getTarget()->getPosition() == key.first))
		{
			m_connectionList[i]->setWalkable(true);
		}
	}
}

void NavMesh::reduceConnections()
{
	for (size_t i = 0; i < m_edges.size(); i++)
	{
		if (numFacesWithEdge(m_edges[i]) == 2)
		{
			removeConnection(m_edges[i]);
		}
	}
}

bool NavMesh::edgeExists(Vec3 a, Vec3 b, EdgeList edges)
{
	Edge test1 = Edge(a, b);
	Edge test2 = Edge(b, a);
	for (size_t i = 0; i < edges.size(); i++)
	{
		Edge reverse = Edge(edges[i].second, edges[i].first);

		if (test1 == edges[i] || test1 == reverse || test2 == edges[i] || test2 == reverse)
			return true;
	}
	return false;
}

bool NavMesh::cleanFace(Face key)
{
	//Remove faces that have edge inside of it
	for (size_t j = 0; j < key.edges.size(); j++)
	{
		for (size_t k = 0; k < key.edges.size(); k++)
		{
			Edge firstEdge = key.edges[j];
			Edge secondEdge = key.edges[k];
			if (firstEdge.first != secondEdge.first && firstEdge.first != secondEdge.second && firstEdge.second != secondEdge.first && firstEdge.second != secondEdge.second)
			{
				for (size_t f = 0; f < m_edges.size(); f++)
				{
					Edge intersectionEdge = m_edges[f];
					Edge reverseEdge = Edge(intersectionEdge.second, intersectionEdge.first);
					if (std::find(key.edges.begin(), key.edges.end(), intersectionEdge) != key.edges.end() || std::find(key.edges.begin(), key.edges.end(), reverseEdge) != key.edges.end())
						continue;
					
					Vec3 point1, point2;
					if ((getIntersection(intersectionEdge, firstEdge.first) || getIntersection(intersectionEdge, firstEdge.second)) && (getIntersection(intersectionEdge, secondEdge.first) || getIntersection(intersectionEdge, secondEdge.second)))
					{
						return false;
					}
				}
			}
		}
	}
	return true;
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

bool NavMesh::faceExists(Face a)
{
	for (size_t i = 0; i < m_faces.size(); i++)
	{
		Face b = m_faces[i];
		if (a.edges.size() == b.edges.size())
		{
			int matches = 0;
			for (size_t j = 0; j < a.edges.size(); j++)
			{
				Edge reverse(a.edges[j].second, a.edges[j].first);
				if (std::find(b.edges.begin(), b.edges.end(), a.edges[j]) != b.edges.end() || std::find(b.edges.begin(), b.edges.end(), reverse) != b.edges.end())
				{
					matches++;
				}
			}

			if (matches == a.edges.size())
			{
				return true;
			}
		}
	}
	return false;
}

int NavMesh::numFacesWithEdge(Edge key)
{
	int matches = 0;
	for (size_t i = 0; i < m_faces.size(); i++)
	{
		if (reverseExists(m_faces[i].edges, key))
		{
			matches++;
		}
	}
	return matches;
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

FaceList NavMesh::getFaces() const
{
	return m_faces;
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

size_t NavMesh::faceCount() const
{
	return m_faces.size();
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
