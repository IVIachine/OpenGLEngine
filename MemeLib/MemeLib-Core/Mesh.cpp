#include "Mesh.h"
#include <vector>

Mesh::Mesh(Vertex* vertices, size_t numVertices, size_t* indices, size_t numIndices, bool isSkyBox)
{
	m_drawCount = numIndices;
	m_isSkyBox = isSkyBox;
	glGenVertexArrays(1, &m_vertexArrayObject);
	glBindVertexArray(m_vertexArrayObject);


	std::vector<Vec3> positions;
	std::vector<Vec2> coords;

	positions.reserve(numVertices);
	coords.reserve(numVertices);

	for (size_t i = 0; i < numVertices; i++)
	{
		positions.push_back(*vertices[i].getPosition());
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
	mNavVertices = model.actualPositions;
	mNavIndices = model.actualIndices;
	mNavFaceCount = m_drawCount;
	
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

Mesh::Mesh(const Mesh & copy)
{
	m_vertexArrayObject = copy.m_vertexArrayObject;
	m_drawCount = copy.m_drawCount;
	m_isSkyBox = copy.m_isSkyBox;

	for (size_t i = 0; i < NUM_BUFFERS; i++)
	{
		mVertexArrayBuffers[i] = copy.mVertexArrayBuffers[i];
	}
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
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		glDrawElements(GL_TRIANGLES, m_drawCount, GL_UNSIGNED_INT, 0);
	}
	else
	{
		glCullFace(GL_BACK);
		//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		glDrawElements(GL_TRIANGLES, m_drawCount, GL_UNSIGNED_INT, 0);
	}

	glBindVertexArray(0);
}
