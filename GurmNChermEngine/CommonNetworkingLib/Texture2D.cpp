#include "Texture2D.h"

Texture2D::Texture2D()
{
	m_sf_texture = sf::Texture();
	m_size = Vector2::ZERO;
}

Texture2D::Texture2D(const size_t width, const size_t height)
{
	m_sf_texture = sf::Texture();
	m_size = Vector2((float)width, (float)height);
}

Texture2D::Texture2D(const std::string filename)
{
	loadFromFile(filename);
}


Texture2D::Texture2D(const Texture2D& copy)
{
	loadFromFile(copy.m_filename);
}

Texture2D::~Texture2D()
{
}


bool Texture2D::loadFromFile(std::string filename)
{
	m_filename = filename;

	m_sf_texture = sf::Texture();

	if (!m_sf_texture.loadFromFile(m_filename))
	{
		std::cout << "Error, cannot open'" << m_filename << "'\n";
		return false;
	}

	m_size = Vector2((float)m_sf_texture.getSize().x, (float)m_sf_texture.getSize().y);

	return true;
}

Vector2 Texture2D::getSize()
{
	return m_size;
}