#include "NavigationMesh.h"
#include <algorithm>
#include "Connection.h"

NavigationMesh::NavigationMesh()
{
}

NavigationMesh::~NavigationMesh()
{
}


void NavigationMesh::constructMesh(std::vector<Point> vertices, std::vector<size_t> indices, size_t faceCount)
{
	std::vector<Edge> edges;
	splitTriangles(vertices, indices, edges, faceCount); //Split the intersections into multiple edges for accuracy
	m_vertices = vertices;
	m_edges = edges;

	mNodes.resize(m_vertices.size(), NULL);

	for (size_t i = 0; i < m_vertices.size(); i++)
	{
		Node* pNode = new Node(i, m_vertices[i]);
		mNodes[i] = pNode;
	}


	for (size_t j = 0; j < m_vertices.size(); j++)
	{
		Node* pFromNode = mNodes[j];
		std::vector<Connection*> connections;

		std::vector<Edge> knownConnections = getKnownConnections(m_vertices[j]);

		for (size_t k = 0; k < knownConnections.size(); k++)
		{
			Node* pToNode = getOtherNode(knownConnections[k], pFromNode);//find to node
			Connection* pConnection;
			float dist = (float)(pFromNode->getPosition() - pToNode->getPosition()).length();
			pConnection = new Connection(pFromNode, pToNode, dist);

			mConnections.push_back(pConnection);
			connections.push_back(pConnection);
		}

		mConnectionMap[j] = connections;
	}
}

void NavigationMesh::splitTriangles(
	std::vector<Point>& vertices, 
	std::vector<size_t> indices, 
	std::vector<Edge>& edges, 
	size_t faceCount)
{

	std::vector<Face> faces;

	gatherEdges(edges, faces, vertices, indices, faceCount);

	// compare edges to each other
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
			Point ip;
			if (getIntersection(edges[i], edges[j], ip))
			{
				// add vertice if not exists
				if (std::find(vertices.begin(), vertices.end(), ip) == vertices.end())
				{
					vertices.push_back(ip);
				}

				// ignore if ip is first or second of edge
				if (ip == edges[i].first || ip == edges[i].second)
				{
					continue;
				}

				// add new edge
				edges.push_back({ ip, edges[i].second });

				// resize old edge
				edges[i].second = ip;
			}
		}
	}

}


bool NavigationMesh::containsVertice(std::vector<Point> vertices, Point key)
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

bool NavigationMesh::reverseExists(std::vector<Edge> edges, Edge key)
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


void NavigationMesh::gatherEdges(std::vector<Edge>& edges, std::vector<Face>& faces, std::vector<Point>& vertices, std::vector<size_t> indices, size_t faceCount)
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


std::vector<Edge> NavigationMesh::getKnownConnections(Point key)
{
	std::vector<Edge> result;
	for (size_t i = 0; i < m_edges.size(); i++)
	{
		if (m_edges[i].first == key || m_edges[i].second == key)
			result.push_back(m_edges[i]);
	}
	return result;
}

Node * NavigationMesh::getOtherNode(Edge tmp, Node* key)
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

std::vector<Face> NavigationMesh::getEdgeFaces(std::vector<Face>& faces, Edge key)
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

float NavigationMesh::norm2(Point v)
{
	return v.x * v.x + v.y * v.y + v.z * v.z;
}

/*edges.erase(edges.begin() + i);
edges.erase(edges.begin() + j); //Remove the edges of the intersection*/


bool NavigationMesh::getIntersection(Edge one, Edge two, Point& ip)
{
	//CITE: http://stackoverflow.com/questions/2316490/the-algorithm-to-find-the-point-of-intersection-of-two-3d-line-segment

	if (one.first == two.first || one.first == two.second || one.second == two.first || one.first == two.second) //edges share a point
	{
		false;
	}

	Point da = one.second - one.first;
	Point db = two.second - two.first;
	Point dc = two.first - one.first;

	if (glm::dot(dc, glm::cross(da, db)) != 0.f)
	{
		return false;
	}

	float s = glm::dot(glm::cross(dc, db), glm::cross(da, db)) / norm2(glm::cross(da, db));

	if (s >= 0.0f && s <= 1.0f)
	{
		ip = one.first + da * Point(s, s, s);

		return true;
	}

	return false;
}

const float EPSILON = 0.001f;
bool NavigationMesh::getIntersection(Edge edge, Point point)
{
	Point linePointA = edge.first;
	Point linePointB = edge.second;

	float a = (linePointB.y - linePointA.y) / (linePointB.x - linePointB.x);
	float b = linePointA.y - a * linePointA.x;
	if (fabs(point.y - (a*point.x + b)) < EPSILON)
	{
		return true;
	}

	return false;
}