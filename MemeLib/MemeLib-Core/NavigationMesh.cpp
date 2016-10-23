#include "NavigationMesh.h"
#include <algorithm>
#include "Connection.h"

NavigationMesh::NavigationMesh()
{
}

NavigationMesh::~NavigationMesh()
{
}


void NavigationMesh::constructMesh(std::vector<glm::vec3> vertices, std::vector<size_t> indices, size_t faceCount)
{
	std::vector<Edge> edges;
	splitTriangles(vertices, indices, edges, faceCount); //Split the intersections into multiple edges for accuracy
	mVerts = vertices;
	mEdges = edges;

	mNodes.resize(mVerts.size(), NULL);

	for (size_t i = 0; i < mVerts.size(); i++)
	{
		Node* pNode = new Node(i, mVerts[i]);
		mNodes[i] = pNode;
	}


	for (size_t j = 0; j < mVerts.size(); j++)
	{
		Node* pFromNode = mNodes[j];
		std::vector<Connection*> connections;

		std::vector<Edge> knownConnections = getKnownConnections(mVerts[j]);

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

void NavigationMesh::splitTriangles(std::vector<glm::vec3>& vertices, std::vector<size_t> indices, std::vector<Edge>& edges, size_t faceCount)
{
	bool isChecking = true;
	std::vector<FaceTemp> faces;

	gatherEdges(edges, faces, vertices, indices, faceCount); //Generate basic edges
	size_t totalTraverse = edges.size();
	int splitCount = 0;

	while (isChecking)
	{
		isChecking = false;
		for (size_t i = 0; i < totalTraverse; i++)
		{
			for (size_t j = 0; j < totalTraverse; j++)
			{
				glm::vec3 inter = getIntersection(edges[i], edges[j]);
				if (inter != glm::vec3(INFINITY, INFINITY, INFINITY))
				{
					if (std::find(vertices.begin(), vertices.end(), inter) == vertices.end())
					{
						splitCount++;
						vertices.push_back(inter);

						Edge 
							first, second, third, fourth, tmp1, tmp2;
						FaceTemp 
							faceTmp1, faceTmp2, faceTmp3, faceTmp4,
							firstFace, secondFace, thirdFace, fourthFace;

						tmp1 = edges[i];
						tmp2 = edges[j];

						edges.erase(edges.begin() + i);
						edges.erase(edges.begin() + j); //Remove the edges of the intersection

						first.first = inter;
						second.first = inter;
						third.first = inter;
						fourth.first = inter;

						first.second = tmp1.first;
						second.second = tmp1.second;
						third.second = tmp2.first;
						fourth.second = tmp2.second;

						edges.push_back(first);
						edges.push_back(second);
						edges.push_back(third);
						edges.push_back(fourth);
						isChecking = true;
					}
				}
			}
		}
	}

}


bool NavigationMesh::containsVertice(std::vector<glm::vec3> vertices, glm::vec3 key)
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


void NavigationMesh::gatherEdges(std::vector<Edge>& edges, std::vector<FaceTemp>& faces, std::vector<glm::vec3>& vertices, std::vector<size_t> indices, size_t faceCount)
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

		FaceTemp faceTemp;
		faceTemp.edges.push_back(tmp);
		faceTemp.edges.push_back(tmp2);
		faceTemp.edges.push_back(tmp3);
		faces.push_back(faceTemp);
	}
}


std::vector<Edge> NavigationMesh::getKnownConnections(glm::vec3 key)
{
	std::vector<Edge> result;
	for (size_t i = 0; i < mEdges.size(); i++)
	{
		if (mEdges[i].first == key || mEdges[i].second == key)
			result.push_back(mEdges[i]);
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

//CITE: http://stackoverflow.com/questions/2316490/the-algorithm-to-find-the-point-of-intersection-of-two-3d-line-segment
glm::vec3 NavigationMesh::getIntersection(Edge one, Edge two)
{
	if (one.first == two.first || one.first == two.second || one.second == two.first || one.first == two.second) //edges share a point
		return glm::vec3(INFINITY, INFINITY, INFINITY);

	glm::vec3 da = one.second - one.first;
	glm::vec3 db = two.second - two.first;
	glm::vec3 dc = two.first - one.first;

	if (glm::dot(dc, glm::cross(da, db)) != 0)
		return glm::vec3(INFINITY, INFINITY, INFINITY);

	float s = glm::dot(glm::cross(dc, db), glm::cross(da, db)) / norm2(glm::cross(da, db));

	if (s >= 0.0 && s <= 1.0)
	{
		return one.first + da * glm::vec3(s, s, s);
	}
	return glm::vec3(INFINITY, INFINITY, INFINITY);
}

std::vector<FaceTemp> NavigationMesh::getEdgeFaces(std::vector<FaceTemp>& faces, Edge key)
{
	std::vector<FaceTemp> faceResult;
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

float NavigationMesh::norm2(glm::vec3 v)
{
	return v.x * v.x + v.y * v.y + v.z * v.z;
}

/*for each face F
{
for each edge (u,v) of F
{
Edges[ pair(u,v) ] = new HalfEdge();
Edges[ pair(u,v) ]->face = F;
}
for each edge (u,v) of F
{
set Edges[ pair(u,v) ]->nextHalfEdge to next half-edge in F
if ( Edges.find( pair(v,u) ) != Edges.end() )
{
Edges[ pair(u,v) ]->oppositeHalfEdge = Edges[ pair(v,u) ];
Edges[ pair(v,u) ]->oppositeHalfEdge = Edges[ pair(u,v) ];
}
}
}*/
