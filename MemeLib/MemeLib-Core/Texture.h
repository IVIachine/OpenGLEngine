#ifndef TEXTURE
#define TEXTURE

#include <string>
#include "Shader.h"
#include "Mesh.h"
#include "Graphics.h"
#include "FreeImage.h"

class Texture : public Trackable
{
public:
	Texture() {};
	Texture(const Texture& copy);
	~Texture();

	void generateNormal(const std::string& filename);
	void bind(size_t unit);

	size_t	getWidth()	const { return m_width; };
	size_t	getHeight() const { return m_height; };

private:
	GLuint		mp_texture;
	GLuint		m_vertexID;
	size_t		m_height;
	size_t		m_width;
	GLubyte*	m_Map;

	Texture(const std::string& imagepath);

	friend class ResourceManager;
}; 
#endif