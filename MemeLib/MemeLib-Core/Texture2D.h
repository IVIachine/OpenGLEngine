#ifndef IMAGE_H
#define IMAGE_H

#include "Shader.h"
#include "Mesh.h"
#include "Texture.h"
#include "Transform.h"

class Texture2D : public Trackable
{
public:
	Texture2D();
	Texture2D(const Texture2D& copy);
	~Texture2D();

	Transform&	transform() { return m_transform; };
	void		setTransform(Transform transform) { m_transform = transform; };

	void		draw(Camera& camera) const;

	size_t		getWidth()	const { return mp_texture->getWidth(); };
	size_t		getHeight() const { return mp_texture->getHeight(); };

	Shader*		getShader() const { return mp_shader; };
	Texture*	getTexture2D() const { return mp_texture; };

private:
	Vector2		m_position;

	Mesh*		mp_mesh;
	Shader*		mp_shader;
	Texture*	mp_texture;
	Vertex*		m_vertices;
	Transform	m_transform;
	bool		m_isCubeMap;

	Texture2D(Texture* texture, Shader* shader);

	friend class ResourceManager;
};
#endif
