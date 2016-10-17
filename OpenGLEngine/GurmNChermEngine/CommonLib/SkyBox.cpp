#include "SkyBox.h"
#include <iostream>
#include <string>
#include <gtx\type_trait.hpp>

SkyBox::SkyBox(const char* shaderPath, const char* imagePath)
{
	m_mesh = new Mesh("cube.obj");
	m_shader = new Shader(shaderPath);
	loadTexture(imagePath);
}


SkyBox::~SkyBox()
{
}

void SkyBox::loadTexture(const char * imagePath)
{
	glActiveTexture(GL_TEXTURE0);
	glGenTextures(1, &m_Texture);
	glBindTexture(GL_TEXTURE_CUBE_MAP, m_Texture);
	char digits[10] = { '0', '1', '2', '3', '4', '5', '6', '7', '8', '9' };
	for (int i = 0; i < 6; i++)
	{
		std::string fileName = imagePath;
		fileName.insert(fileName.begin(), digits[i]);

		FREE_IMAGE_FORMAT format = FreeImage_GetFileType(fileName.c_str(), 0);//Automatocally detects the format
		FIBITMAP* image = FreeImage_Load(format, fileName.c_str());

		FIBITMAP* temp = image;
		image = FreeImage_ConvertTo32Bits(image);
		FreeImage_Unload(temp);

		m_texWidth = FreeImage_GetWidth(image);
		m_texHeight = FreeImage_GetHeight(image);

		m_Map = new GLubyte[4 * m_texWidth * m_texHeight];
		char*pixels = (char*)FreeImage_GetBits(image);

		for (int j = 0; j < m_texWidth*m_texHeight; j++)
		{
			m_Map[j * 4 + 0] = pixels[j * 4 + 2];
			m_Map[j * 4 + 1] = pixels[j * 4 + 1];
			m_Map[j * 4 + 2] = pixels[j * 4 + 0];
			m_Map[j * 4 + 3] = pixels[j * 4 + 3];
		}

		//May need GL_RGB
		glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGBA, m_texWidth, m_texHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, m_Map);

		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR); //Smoothens texture
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
		FreeImage_Unload(image);
	}
	m_uniform = glGetUniformLocation(m_shader->getProgram(), "SkyBoxTexture");
	glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
}

void SkyBox::draw(Camera camera)
{
	//3. Activate the texture unit
	m_shader->bind();
	glUniformMatrix4fv(glGetUniformLocation(m_shader->getProgram(), "modelViewProjectionMatrix"), 1, GL_FALSE, glm::value_ptr(camera.getViewProjection()));
	glActiveTexture(GL_TEXTURE0 + 0);
	glBindTexture(GL_TEXTURE_2D, m_Texture);
	m_mesh->draw();
}

void SkyBox::update()
{
}

