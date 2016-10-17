#include "Image.h"



Image::Image()
{
}


Image::Image(const std::string & fileName, Vertex * vertices, unsigned int numVertices, const char * imagepath, unsigned int* indices, unsigned int numIndices, bool isCubeMap)
{
	m_vertices = vertices;
	m_shader = new Shader(fileName);
	m_mesh = new Mesh(m_vertices, numVertices, indices, numIndices, isCubeMap);
	m_texture = new Texture(imagepath);
	m_transform = Transform(glm::vec3(0,0,0), glm::vec3(0,0,0));
}

Image::Image(const std::string & fileName, const char * imagepath, const char * meshPath, bool isCubeMap)
{
	m_shader = new Shader(fileName);
	m_mesh = new Mesh("cube.obj");
	m_texture = new Texture(imagepath);
	m_transform = Transform(glm::vec3(0, 0, 0), glm::vec3(0, 0, 0));
	m_isCubeMap = isCubeMap;
}

Image::~Image()
{
	delete m_shader;
	m_shader = NULL;
	delete m_mesh;
	m_mesh = NULL;
	delete m_texture;
	m_texture = NULL;
}

void Image::draw(Camera& camera)
{
	m_shader->bind();
	m_texture->bind(0);
	m_shader->update(m_transform, camera);
	m_mesh->draw();
}
