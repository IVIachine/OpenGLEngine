#ifndef IMAGE_H
#define IMAGE_H

#include "Shader.h"
#include "Mesh.h"
#include "Texture.h"
#include "Transform.h"


//Cite::https://www.youtube.com/watch?v=17axYo6mKhY&index=9&list=PLEETnX-uPtBXT9T-hD0Bj31DSnwio-ywh
class Image
{
private:
	Mesh* m_mesh;
	Shader* m_shader;
	Texture* m_texture;
	Vertex* m_vertices;
	Transform m_transform;
	bool m_isCubeMap;
public:
	Image(const std::string& fileName, Vertex* vertices, unsigned int numVertices, const char * imagepath, unsigned int* indices, unsigned int numIndices, bool isCubeMap);
	Image(const std::string & fileName, const char * imagepath, const char * meshPath, bool isCubeMap);
	Image();
	~Image();

	void draw(Camera& camera);
	void setTransform(Transform transform) { m_transform = transform; };
};
#endif
