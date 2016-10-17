#include "Texture.h"
#include <iostream>
#include <vector>
#include <fstream>
#include <cassert>

Texture::Texture(const char * imagepath)
{
	genNormal(imagepath);
}

Texture::~Texture()
{
	glDeleteTextures(1, &m_Texture);
}

void Texture::genNormal(const char * imagePath)
{
	FREE_IMAGE_FORMAT format = FreeImage_GetFileType(imagePath, 0);//Automatocally detects the format
	FIBITMAP* image = FreeImage_Load(format, imagePath);

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


	glGenTextures(1, &m_Texture);
	glBindTexture(GL_TEXTURE_2D, m_Texture);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR); //Deals with reducing texture
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, m_texWidth, m_texHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, m_Map);
	glBindTexture(GL_TEXTURE_2D, 0); //May need to delete
}

void Texture::bind(unsigned int unit)
{
	assert(unit >= 0 && unit <= 31);

	glActiveTexture(GL_TEXTURE0 + unit);
	glBindTexture(GL_TEXTURE_2D, m_Texture);
}
