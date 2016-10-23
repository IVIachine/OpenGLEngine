#include "Volume.h"

Volume::Volume()
{
}


Volume::Volume(Shader* shader, Vertex* vertices, Texture* texture, unsigned int numVertices, unsigned int* indices, unsigned int numIndices, bool isCubeMap)
{
	m_vertices = vertices;
	mp_shader = shader;
	mp_mesh = new Mesh(m_vertices, numVertices, indices, numIndices, isCubeMap);
	mp_texture = texture;
	m_transform = Transform(glm::vec3(0, 0, 0), glm::vec3(0, 0, 0));
}

Volume::Volume(Shader* shader, Texture* texture, const char * volumePath, bool isCubeMap, NavigationMesh* nav)
{
	mp_shader = shader;
	mp_mesh = new Mesh(volumePath, nav);
	mp_texture = texture;
	m_transform = Transform(glm::vec3(0, 0, 0), glm::vec3(0, 0, 0));
	m_isCubeMap = isCubeMap;
}

Volume::~Volume()
{
	delete mp_mesh;
	mp_mesh = NULL;
}


void Volume::draw(Camera& camera)
{
	mp_shader->bind();
	mp_texture->bind(0);
	mp_shader->update(m_transform, camera);
	mp_mesh->draw();
}


void Volume::deserialize(std::istream & in)
{

}

void Volume::serialize(std::ostream & out) const
{

}
