#include "Mesh.h"
#include <vector>

Mesh::Mesh(Vertex* vertices, unsigned int numVertices, unsigned int* indices, unsigned int numIndices, bool isSkyBox)
{
	m_drawCount = numIndices;
	m_isSkyBox = isSkyBox;
	glGenVertexArrays(1, &m_vertexArrayObject);
	glBindVertexArray(m_vertexArrayObject);


	std::vector<glm::vec3> positions;
	std::vector<glm::vec2> coords;

	positions.reserve(numVertices);
	coords.reserve(numVertices);

	for (unsigned int i = 0; i < numVertices; i++)
	{
		positions.push_back(*vertices[i].getPos());
		coords.push_back(*vertices[i].getCoord());
	}

	glGenBuffers(NUM_BUFFERS, mVertexArrayBuffers); //Allocate space for the buffers
	glBindBuffer(GL_ARRAY_BUFFER, mVertexArrayBuffers[POSITION_VB]); //Treat as an array
	glBufferData(GL_ARRAY_BUFFER, numVertices * sizeof(positions[0]), &positions[0], GL_STATIC_DRAW); //Move data to gpu memory

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0); //Second arg is how much data. ex 1 vec3 is 3 floats... Second to last is how much to skip, last is ptr to beginning

	glBindBuffer(GL_ARRAY_BUFFER, mVertexArrayBuffers[TEXCOORD_VB]); //Treat as an array
	glBufferData(GL_ARRAY_BUFFER, numVertices * sizeof(coords[0]), &coords[0], GL_STATIC_DRAW); //Move data to gpu memory

	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, 0);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mVertexArrayBuffers[INDEX_VB]); //Treat as an array
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, numIndices * sizeof(indices[0]), &indices[0], GL_STATIC_DRAW); //Move data to gpu memory

	glBindVertexArray(0);
}

Mesh::Mesh(std::string fileName)
{
	m_isSkyBox = false;
	glGenVertexArrays(1, &m_vertexArrayObject);
	glBindVertexArray(m_vertexArrayObject);

	IndexedModel model = OBJModel(fileName).ToIndexedModel();

	m_drawCount = model.indices.size();

	glGenBuffers(NUM_BUFFERS, mVertexArrayBuffers); //Allocate space for the buffers
	glBindBuffer(GL_ARRAY_BUFFER, mVertexArrayBuffers[POSITION_VB]); //Treat as an array
	glBufferData(GL_ARRAY_BUFFER, model.positions.size() * sizeof(model.positions[0]), &model.positions[0], GL_STATIC_DRAW); //Move data to gpu memory

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0); //Second arg is how much data. ex 1 vec3 is 3 floats... Second to last is how much to skip, last is ptr to beginning

	glBindBuffer(GL_ARRAY_BUFFER, mVertexArrayBuffers[TEXCOORD_VB]); //Treat as an array
	glBufferData(GL_ARRAY_BUFFER, model.positions.size() * sizeof(model.texCoords[0]), &model.texCoords[0], GL_STATIC_DRAW); //Move data to gpu memory

	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, 0);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mVertexArrayBuffers[INDEX_VB]); //Treat as an array
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, model.indices.size() * sizeof(model.indices[0]), &model.indices[0], GL_STATIC_DRAW); //Move data to gpu memory

	glBindVertexArray(0);
}

Mesh::~Mesh()
{
	glDeleteVertexArrays(1, &m_vertexArrayObject);
}

void Mesh::draw()
{
	glBindVertexArray(m_vertexArrayObject);
	if (m_isSkyBox)
	{
		glCullFace(GL_FRONT);
		glDrawElements(GL_TRIANGLES, m_drawCount, GL_UNSIGNED_INT, 0);
	}
	else
	{
		glCullFace(GL_BACK);
		glDrawElements(GL_TRIANGLES, m_drawCount, GL_UNSIGNED_INT, 0);
	}

	glBindVertexArray(0);
}
