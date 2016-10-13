#ifndef _TEXTURE2D_H_
#define _TEXTURE2D_H_

#include <SFML/Graphics.hpp>
#include "Vector2.h"

class Texture2D
{
public:
	Texture2D(const Texture2D& copy);
	~Texture2D();

	Vector2		getSize();
	std::string toString() { return m_filename; }

private:
	Texture2D();
	Texture2D(const size_t width, const size_t height);
	Texture2D(const std::string filename);

	sf::Texture m_sf_texture;
	std::string m_filename;
	Vector2		m_size;

	bool		loadFromFile(std::string filename);

	friend class Sprite;
	friend class Shader;
	friend class Texture2DManager;
};

#endif