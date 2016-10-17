#ifndef MESH_H
#define MESH_H

#include <glm.hpp>
#include <GL\glew.h>
#include "ObjLoader.h"

class Vertex
{
public:
	Vertex(const glm::vec3& pos, const glm::vec2 coord)
	{
		m_pos = pos;
		m_textCoord = coord;
	}
	Vertex() {};

	inline glm::vec3* getPos() { return &m_pos; };
	inline glm::vec2* getCoord() { return &m_textCoord; };
protected:

private:
	glm::vec3 m_pos;
	glm::vec2 m_textCoord;
};

class Mesh
{
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
	unsigned int m_drawCount; 
	bool m_isSkyBox;

public:
	Mesh(Vertex* vertices, unsigned int numVertices, unsigned int* indices, unsigned int numIndices, bool isSkyBox);
	Mesh(std::string fileName);
	Mesh() {};
	~Mesh();

	void draw();
};
#endif
