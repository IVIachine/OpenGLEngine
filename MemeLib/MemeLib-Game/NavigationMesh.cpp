#include "NavigationMesh.h"
#include <algorithm>
#include "Connection.h"
#include "Vector3.h"

NavigationMesh::NavigationMesh()
{
}

NavigationMesh::~NavigationMesh()
{
}


void NavigationMesh::constructMesh(Mesh* mesh)
{
	std::vector<Edge> edges;
	std::vector<_vec3> verts = mesh->getVerts();
	splitTriangles(verts, mesh->getIndices(), edges, mesh->getCount()); //Split the intersections into multiple edges for accuracy
	m_vertices = verts;
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

		std::vector<Edge> knownConnections = getKnownConnections(pFromNode->getPosition());

		for (size_t k = 0; k < knownConnections.size(); k++)
		{
			Node* pToNode = getOtherNode(knownConnections[k], pFromNode);//find to node
			Connection* pConnection;
			float dist;
			float dx, dy, dz;
			dx = pFromNode->getX() - pToNode->getX();
			dy = pFromNode->getY() - pToNode->getY();
			dz = pFromNode->getZ() - pToNode->getZ();
			dist = sqrt(dx*dx + dy*dy + dz*dz);

			pConnection = new Connection(pFromNode, pToNode, dist);

			mConnections.push_back(pConnection);
			connections.push_back(pConnection);
		}

		mConnectionMap[j] = connections;
	}
}

void NavigationMesh::splitTriangles(
	std::vector<_vec3>& vertices, 
	std::vector<size_t> indices, 
	std::vector<Edge>& edges, 
	size_t faceCount)
{
	std::vector<Face> faces;
	gatherEdges(edges, faces, vertices, indices, faceCount);

	//std::vector<Edge>  copyEdges(edges);
	//std::vector<_vec3> copyVerts(vertices);

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
			_vec3 ip;
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
			_vec3 ip = vertices[j];

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


bool NavigationMesh::containsVertice(std::vector<_vec3> vertices, _vec3 key)
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


void NavigationMesh::gatherEdges(std::vector<Edge>& edges, std::vector<Face>& faces, std::vector<_vec3>& vertices, std::vector<size_t> indices, size_t faceCount)
{
	for (size_t i = 0; i < vertices.size(); i++)
	{
		vertices[i].x = -vertices[i].x;
		vertices[i].z = -vertices[i].z;
		vertices[i].x += 2.5;
	}

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


std::vector<Edge> NavigationMesh::getKnownConnections(_vec3 key)
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

float NavigationMesh::norm2(_vec3 v) const
{
	return v.x * v.x + v.y * v.y + v.z * v.z;
}


bool NavigationMesh::getIntersection(Edge one, Edge two, _vec3& ip) const
{
	//CITE: http://stackoverflow.com/questions/2316490/the-algorithm-to-find-the-point-of-intersection-of-two-3d-line-segment

	if (one.first == two.first || one.first == two.second || one.second == two.first || one.first == two.second) //edges share a point
	{
		false;
	}

	_vec3 da = one.second - one.first;
	_vec3 db = two.second - two.first;
	_vec3 dc = two.first - one.first;

	if (glm::dot(dc, glm::cross(da, db)) != 0.f)
	{
		return false;
	}

	float s = glm::dot(glm::cross(dc, db), glm::cross(da, db)) / norm2(glm::cross(da, db));

	if (s >= 0.0f && s <= 1.0f)
	{
		ip = one.first + da * _vec3(s, s, s);

		return true;
	}

	return false;
}

bool NavigationMesh::getIntersection(Edge edge, _vec3 point) const
{
	_vec3 a = edge.first;
	_vec3 b = edge.second;
	_vec3 c = point;

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

