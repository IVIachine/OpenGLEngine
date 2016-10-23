#include "NavigationMesh.h"
#include <algorithm>


NavigationMesh::NavigationMesh()
{
}


NavigationMesh::~NavigationMesh()
{
}

void NavigationMesh::constructMesh(std::vector<glm::vec3> vertices, std::vector<size_t> indices, size_t faceCount)
{
	std::vector<EdgeTemp> edges;
	splitTriangles(vertices, indices, edges, faceCount); //Split the intersections into multiple edges for accuracy
	mVerts = vertices;
	mEdges = edges;
}

void NavigationMesh::splitTriangles(std::vector<glm::vec3>& vertices, std::vector<size_t> indices, std::vector<EdgeTemp>& edges, size_t faceCount)
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
						EdgeTemp first, second, third, fourth, tmp1, tmp2;
						FaceTemp faceTmp1, faceTmp2, faceTmp3, faceTmp4, firstFace, secondFace, thirdFace, fourthFace;

						tmp1 = edges[i];
						tmp2 = edges[j];

						edges.erase(edges.begin() + i);
						edges.erase(edges.begin() + j); //Remove the edges of the intersection

						first.mFirst = inter;
						second.mFirst = inter;
						third.mFirst = inter;
						fourth.mFirst = inter;

						first.mSecond = tmp1.mFirst;
						second.mSecond = tmp1.mSecond;
						third.mSecond = tmp2.mFirst;
						fourth.mSecond = tmp2.mSecond;

						edges.push_back(first);
						edges.push_back(second);
						edges.push_back(third);
						edges.push_back(fourth);
						isChecking = true;
				
						/*std::vector<FaceTemp> firstFaces, secondFaces;
						firstFaces = getEdgeFaces(faces, tmp1);
						secondFaces = getEdgeFaces(faces, tmp2);

						if (firstFaces.size() > 1 && secondFaces.size() > 1) //Edges to split has multiple faces
						{
							faceTmp1 = firstFaces[0];
							faceTmp2 = firstFaces[1];
							faceTmp3 = secondFaces[0];
							faceTmp4 = secondFaces[1];

							faces.erase(std::remove(faces.begin(), faces.end(), faceTmp1), faces.end());
							faces.erase(std::remove(faces.begin(), faces.end(), faceTmp2), faces.end());
							faces.erase(std::remove(faces.begin(), faces.end(), faceTmp3), faces.end());
							faces.erase(std::remove(faces.begin(), faces.end(), faceTmp4), faces.end());
						}
						else if (firstFaces.size() == 1 && secondFaces.size() > 1) //Second edge has more than 1 face
						{
							faceTmp1 = firstFaces[0];
							faceTmp3 = secondFaces[0];
							faceTmp4 = secondFaces[1];
						}
						else if (firstFaces.size() > 1 && secondFaces.size() == 1) //First edge has more than 1 face
						{
							faceTmp1 = firstFaces[0];
							faceTmp2 = firstFaces[1];
							faceTmp3 = secondFaces[0];
						}
						*/
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

bool NavigationMesh::reverseExists(std::vector<EdgeTemp> edges, EdgeTemp key)
{
	for (size_t i = 0; i < edges.size(); i++)
	{
		if ((edges[i].mFirst == key.mSecond && edges[i].mSecond == key.mFirst) || (edges[i].mFirst == key.mFirst && edges[i].mSecond == key.mSecond))
		{
			return true;
		}
	}
	return false;
}

void NavigationMesh::gatherEdges(std::vector<EdgeTemp>& edges, std::vector<FaceTemp>& faces, std::vector<glm::vec3>& vertices, std::vector<size_t> indices, size_t faceCount)
{
	for (size_t i = 0; i < faceCount; i += 3)
	{
		EdgeTemp tmp, tmp2, tmp3;
		tmp.mFirst = vertices[indices[i]];
		tmp.mSecond = vertices[indices[i + 1]];

		tmp2.mFirst = vertices[indices[i + 1]];
		tmp2.mSecond = vertices[indices[i + 2]];

		tmp3.mFirst = vertices[indices[i + 2]];
		tmp3.mSecond = vertices[indices[i]];

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

//CITE: http://stackoverflow.com/questions/2316490/the-algorithm-to-find-the-point-of-intersection-of-two-3d-line-segment
glm::vec3 NavigationMesh::getIntersection(EdgeTemp one, EdgeTemp two)
{
	if (one.mFirst == two.mFirst || one.mFirst == two.mSecond || one.mSecond == two.mFirst || one.mFirst == two.mSecond) //edges share a point
		return glm::vec3(INFINITY, INFINITY, INFINITY);

	glm::vec3 da = one.mSecond - one.mFirst;
	glm::vec3 db = two.mSecond - two.mFirst;
	glm::vec3 dc = two.mFirst - one.mFirst;

	if (glm::dot(dc, glm::cross(da, db)) != 0)
		return glm::vec3(INFINITY, INFINITY, INFINITY);

	float s = glm::dot(glm::cross(dc, db), glm::cross(da, db)) / norm2(glm::cross(da, db));

	if (s >= 0.0 && s <= 1.0)
	{
		return one.mFirst + da * glm::vec3(s, s, s);
	}
	return glm::vec3(INFINITY, INFINITY, INFINITY);
}

std::vector<FaceTemp> NavigationMesh::getEdgeFaces(std::vector<FaceTemp>& faces, EdgeTemp key)
{
	std::vector<FaceTemp> faceResult;
	bool exists = false;
	for (size_t i = 0; i < faces.size(); i++)
	{
		for (size_t j = 0; j < faces[i].edges.size(); j++)
		{
			if ((faces[i].edges[j].mFirst == key.mFirst && faces[i].edges[j].mSecond == key.mSecond) ||
				(faces[i].edges[j].mFirst.x == key.mSecond.x && faces[i].edges[j].mFirst.z == key.mSecond.z))
			{
				exists = false;

				for (size_t k = 0; k < faceResult.size(); k++)
				{
					if (faces[i].edges.size() != faceResult[k].edges.size())
						break;

					for (size_t f = 0; f < faces[i].edges.size(); f++)
					{
						if ((faces[i].edges[f].mFirst == faceResult[k].edges[f].mFirst && faces[i].edges[f].mSecond == faceResult[k].edges[f].mSecond) ||
							(faces[i].edges[f].mSecond == faceResult[k].edges[f].mFirst && faces[i].edges[f].mFirst == faceResult[k].edges[f].mSecond))
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
