#include "Font.h"

Font::Font()
{
	m_filename = "";
}

Font::Font(const std::string& filename)
{
	m_filename = filename;
}

Font::Font(const Font& copy)
{
	m_filename = copy.m_filename;
}

Font::~Font()
{
}