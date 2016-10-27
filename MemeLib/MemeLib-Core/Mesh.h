#ifndef MESH_H
#define MESH_H

#include "Vertex.h"
#include "ObjLoader.h"
#include "Vector3.h"

class Mesh : public Trackable
{
public:
	Mesh() {};
	Mesh(Vertex* vertices, size_t numVertices, size_t* indices, size_t numIndices, bool isSkyBox);
	Mesh(std::string fileName);
	Mesh(const Mesh& copy);
	~Mesh();
	std::vector<Vec3> getVerts() const { return mNavVertices; };
	std::vector<size_t> getIndices() const { return mNavIndices; };
	size_t getCount() const { return mNavFaceCount; };
	void draw();

private:
	enum
	{
		POSITION_VB,
		TEXCOORD_VB,
		INDEX_VB,
		NUM_BUFFERS
	};

	GLuint m_vertexArrayObject;
	GLuint mVertexArrayBuffers[NUM_BUFFERS];
	size_t m_drawCount;
	std::vector<Vec3> mNavVertices;
	std::vector<size_t> mNavIndices;
	size_t mNavFaceCount;
	bool m_isSkyBox;
};
#endif
