#ifndef TEXTURE
#define TEXTURE
#include <string>
#include "Shader.h"
#include "Mesh.h"
#include "Graphics.h"
#include "FreeImage.h"

class Texture
{
public:
	Texture(const char * imagepath);
	~Texture();

	void genNormal(const char * imagePath);
	void bind(unsigned int unit);
private:
	GLuint m_Texture, vertexID;
	int m_texHeight;
	int m_texWidth;
	GLubyte* m_Map;
}; 
#endif