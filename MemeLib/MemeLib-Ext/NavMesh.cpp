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

	std::cout << toString() << "Building...\n";

	std::cout << toString() << " (1/4) -> Splitting triangles... ";
	m_vertices = mesh->getVerts();
	splitTriangles(m_vertices, mesh->getIndices(), m_edges, mesh->size());
	std::cout << "Done.\n";

	std::cout << toString() << " (2/4) -> Cleaning edges... ";
	cleanEdges();
	std::cout << "Done.\n";

	std::cout << toString() << " (3/4) -> Populating node list... ";
	m_nodeList.resize(m_vertices.size(), NULL);
	for (size_t i = 0; i < m_vertices.size(); i++)
	{
		Node* pNode = new Node(i, m_vertices[i]);
		m_nodeList[i] = pNode;
	}
	std::cout << "Done.\n";

	std::cout << toString() << " (4/4) -> Creating connections... ";
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
	std::cout << "Done.\n";	

	timer.stop();
	std::cout << toString() << " -> Elapsed Time: " << timer.getElapsedTime() << "\n";
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
				if (!faceExists(m_faces, newFace))
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

void NavMesh::cleanEdges()
{
	for (int i = m_edges.size() - 1; i >= 0; --i)
	{
		for (int j = m_edges.size() - 1; j >= 0; --j)
		{
			if (i == j)
				continue;

			Edge reverseEdge = Edge(m_edges[i].second, m_edges[i].first);
			if (m_edges[i] == m_edges[j] || reverseEdge == m_edges[j])
			{
				m_edges.erase(m_edges.begin() + i);
				i = m_edges.size() - 1;
				j = m_edges.size() - 1;
				break;
			}
		}
	}
}

void NavMesh::cleanAllFaces()
{
	for (int j = m_faces.size() - 1; j >= 0; --j)
	{
		bool found = false;
		int count = 0;
		Face key = m_faces[j];
		for (size_t i = 0; i < m_originalFaces.size(); i++)
		{
			Vec3 A = m_originalFaces[i].edges[0].first;
			Vec3 B = m_originalFaces[i].edges[1].first;
			Vec3 C = m_originalFaces[i].edges[2].first;

			Vec3 centerKey = getFaceCenter(key);
			if (pointInTriangle(centerKey, A, B, C))
			{
				found = true;
			}
		}
		if (!found)
		{
			m_faces.erase(m_faces.begin() + j);
			j = m_faces.size() - 1;
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
			if (firstEdge.first != secondEdge.first && firstEdge.first != secondEdge.second && firstEdge.second != secondEdge.first && firstEdge.second != secondEdge.second && j!=k)
			{
				for (size_t f = 0; f < m_edges.size(); f++)
				{
					Edge intersectionEdge = m_edges[f];
					Edge reverseEdge = Edge(intersectionEdge.second, intersectionEdge.first);
					if (std::find(key.edges.begin(), key.edges.end(), intersectionEdge) != key.edges.end() || std::find(key.edges.begin(), key.edges.end(), reverseEdge) != key.edges.end())
						continue;

					Vec3 point1, point2, point3, point4;
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

bool NavMesh::faceExists(FaceList faces, Face a)
{
	for (size_t i = 0; i < faces.size(); i++)
	{
		Face b = faces[i];
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

bool NavMesh::sameSide(Vec3 p1, Vec3 p2, Vec3 a, Vec3 b)
{
	//CITE: http://blackpawn.com/texts/pointinpoly/

	Vec3 cp1 = glm::cross(b - a, p1 - a);
	Vec3 cp2 = glm::cross(b - a, p2 - a);

	if (glm::dot(cp1, cp2) >= 0)
	{
		return true;
	}

	return false;
}

bool NavMesh::pointInTriangle(Vec3 point, Vec3 a, Vec3 b, Vec3 c)
{
	if (sameSide(point, a, b, c) && sameSide(point, b, a, c) && sameSide(point, c, a, b))
		return true;

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

float NavMesh::heighAtCoords(float x, float z)
{
	float dist = INFINITY;
	Vec3 closest;
	Vec3 testPoint(x, 0.0f, z);
	for (size_t i = 0; i < m_vertices.size(); i++)
	{
		float testDist = glm::distance(m_vertices[i], testPoint);
		if (testDist < dist)
		{
			closest = m_vertices[i];
			dist = testDist;
		}
	}

	return closest.y;
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

FaceList NavMesh::getFaceConnections(Face key)
{
	FaceList faces;
	for (size_t i = 0; i < m_faces.size(); i++)
	{
		Face workingFace = m_faces[i];
		for (size_t j = 0; j < key.edges.size(); j++)
		{
			for (size_t k = 0; k < workingFace.edges.size(); k++)
			{
				if ((key.edges[j].first == workingFace.edges[k].first && key.edges[j].second == workingFace.edges[k].second) ||
					(key.edges[j].second == workingFace.edges[k].first && key.edges[j].first == workingFace.edges[k].second))
				{
					if (!faceExists(faces, workingFace))
					{
						faces.push_back(workingFace);
					}
				}
			}
		}
	}
	return faces;
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

Vec3 NavMesh::getFaceCenter(Face key)
{
	Vec3 center;
	for (size_t j = 0; j < key.edges.size(); j++)
	{
		center += key.edges[j].first;
		center += key.edges[j].second;
	}
	center /= key.edges.size() * 2;
	return center;
}

Vec3 NavMesh::getClosestVert(Vec3 key)
{
	Vec3 closest;
	float closestDist = INFINITY;
	for (size_t i = 0; i < m_vertices.size(); i++)
	{
		float dist = glm::distance(key, m_vertices[i]);
		if (dist < closestDist)
		{
			closest = m_vertices[i];
			closestDist = dist;
		}
	}
	return closest;
}

Face NavMesh::getFaceFromVec(Vec3 key)
{
	for (size_t i = 0; i < m_faces.size(); i++)
	{
		if (getFaceCenter(m_faces[i]) == key)
			return m_faces[i];
	}
	return Face();
}
