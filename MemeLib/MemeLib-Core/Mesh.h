#ifndef MESH_H
#define MESH_H

#include "Vertex.h"
#include "ObjLoader.h"

class Mesh : public Trackable
{
public:
	Mesh() {};
	Mesh(Vertex* vertices, size_t numVertices, size_t* indices, size_t numIndices, bool isSkyBox);
	Mesh(std::string fileName);
	Mesh(const Mesh& copy);
	~Mesh();

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
	bool m_isSkyBox;
};
#endif
