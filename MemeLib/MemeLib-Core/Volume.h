#ifndef VOLUME_H
#define VOLUME_H

#include "Shader.h"
#include "Serializable.h"
#include "Mesh.h"
#include "Texture.h"
#include "Transform.h"

class Volume : public Serializable
{
public:
	Volume(Shader* shader, Vertex* vertices, Texture* texture, unsigned int numVertices, unsigned int* indices, unsigned int numIndices, bool isCubeMap);
	Volume(Shader* shader, Texture* texture, const char * volumePath, bool isCubeMap);
	Volume();
	~Volume();
	Transform& transform() { return m_transform; };
	void draw(Camera& camera);
	void setTransform(Transform transform) { m_transform = transform; };

	void deserialize(std::istream& in) override;
	void serialize(std::ostream& out) const override;

private:
	Mesh* mp_mesh;
	Shader* mp_shader;
	Texture* mp_texture;
	Vertex* m_vertices;
	Transform m_transform;
	bool m_isCubeMap;
};
#endif
