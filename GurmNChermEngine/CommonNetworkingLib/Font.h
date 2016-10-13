#ifndef _FONT_H_
#define _FONT_H_

#include <SFML\Graphics\Font.hpp>
#include <SFML\Graphics\Text.hpp>

class Font
{
public:
	Font();
	Font(const Font& copy);
	~Font();

	bool loadFromFile(const std::string filename);

private:
	sf::Font	m_sf_font;
	std::string	m_filename;

	friend class Graphics;
	friend class Text;
};

#endif // !_FONT_H_
