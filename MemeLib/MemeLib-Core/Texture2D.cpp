#include "Texture2D.h"
#include "Maths.h"

Texture2D::Texture2D()
{
	mp_mesh = NULL;
	mp_shader = NULL;
	mp_texture = NULL;
	m_transform = Transform();
	m_isCubeMap = false;
}

Texture2D::Texture2D(Texture* texture, Shader* shader)
{
	mp_texture = texture;
	mp_shader = shader;

	Vertex vertices[] = {
		Vertex(Vec3(-1.0f, -1.0f, 1.0f), Vec2(0.0f, 0.0f)),
		Vertex(Vec3(1.0f, -1.0f, 1.0f), Vec2(1.0f, 0.0f)), 
		Vertex(Vec3(-1.0f, 1.0f, 1.0f), Vec2(0.0f, 1.0f)),  
		Vertex(Vec3(1.0f, 1.0f, 1.0f), Vec2(1.0f, 1.0f)),

	};
	size_t indices[]{
		0,1,3, 0,3,2
	};

	m_vertices = vertices;	

	mp_mesh = new Mesh(
		m_vertices, 
		sizeof(vertices) / sizeof(vertices[0]), 
		indices, 
		sizeof(indices) / sizeof(indices[0]), 
		false);	

	

	m_transform = Transform(Vec3(0, 0, 0), Vec3(0, 0, 0));
}

Texture2D::Texture2D(const Texture2D & copy)
{
	mp_mesh = copy.mp_mesh;
	mp_shader = copy.mp_shader;
	mp_texture = copy.mp_texture;
	m_vertices = copy.m_vertices;
	m_transform = copy.m_transform;
	m_isCubeMap = copy.m_isCubeMap;
}

Texture2D::~Texture2D()
{
	delete mp_mesh;
	mp_mesh = NULL;
}


void Texture2D::draw(Camera& camera) const
{
	mp_shader->bind();
	mp_texture->bind(0);
	mp_shader->update(m_transform, camera);
	mp_mesh->draw();
}
