#ifndef SKYBOX_H
#define SKYBOX_H

#include "Camera.h"
#include "FreeImage.h"
#include <glm.hpp>
#include <GL\glew.h>
#include <gtc\type_ptr.hpp>
#include "Shader.h"
#include "Mesh.h"
class SkyBox
{
private:
	GLuint m_Texture, m_VAO, m_VBO;
	int m_texWidth, m_texHeight;
	GLubyte* m_Map;
	Shader* m_shader;
	Mesh* m_mesh;
	GLuint m_uniform;
public:
	SkyBox(const char* imagePath, const char* shaderPath);
	~SkyBox();

	void loadTexture(const char* imagePath);
	void draw(Camera camera);
	void update();
};
#endif
