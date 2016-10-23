#include "Texture.h"
#include <iostream>
#include <vector>
#include <fstream>
#include <cassert>

Texture::Texture(const std::string& imagepath)
{
	generateNormal(imagepath.c_str());
}

Texture::Texture(const Texture & copy)
{
	mp_texture = copy.mp_texture;
	m_vertexID = copy.m_vertexID;
	m_height = copy.m_height;
	m_width = copy.m_width;
	m_Map = copy.m_Map;
}

Texture::~Texture()
{
	glDeleteTextures(1, &mp_texture);
}


void Texture::generateNormal(const std::string& filename)
{
	const char* imagePath = filename.c_str();

	//Automatocally detects the format
	FREE_IMAGE_FORMAT format = FreeImage_GetFileType(imagePath, 0);
	FIBITMAP* image = FreeImage_Load(format, imagePath);

	FIBITMAP* temp = image;
	image = FreeImage_ConvertTo32Bits(image);
	FreeImage_Unload(temp);

	m_width = FreeImage_GetWidth(image);
	m_height = FreeImage_GetHeight(image);

	m_Map = new GLubyte[4 * m_width * m_height];
	char*pixels = (char*)FreeImage_GetBits(image);

	for (int j = 0; j < m_width*m_height; j++) 
	{
		m_Map[j * 4 + 0] = pixels[j * 4 + 2];
		m_Map[j * 4 + 1] = pixels[j * 4 + 1];
		m_Map[j * 4 + 2] = pixels[j * 4 + 0];
		m_Map[j * 4 + 3] = pixels[j * 4 + 3];
	}


	glGenTextures(1, &mp_texture);
	glBindTexture(GL_TEXTURE_2D, mp_texture);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR); //Deals with reducing texture
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, m_width, m_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, m_Map);
	glBindTexture(GL_TEXTURE_2D, 0); //May need to delete
}

void Texture::bind(size_t unit)
{
	assert(unit >= 0 && unit <= 31);

	glActiveTexture(GL_TEXTURE0 + unit);

	glBindTexture(GL_TEXTURE_2D, mp_texture);
}
