#include "Font.h"

Font::Font()
{
}

Font::Font(const Font& copy)
{
	m_sf_font = copy.m_sf_font;
	m_filename = copy.m_filename;
}

Font::~Font()
{	
}


bool Font::loadFromFile(const std::string filename)
{
	m_filename = filename;
	return m_sf_font.loadFromFile(m_filename);
}