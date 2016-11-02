#include "Font.h"

Font::Font()
{
	m_filename = "";
	m_faceIndex = 0;
	m_size = 12;
}

Font::Font(FT_Library library, std::string filename, size_t size, long faceIndex)
{
	m_filename = filename;
	m_faceIndex = faceIndex;

	if (FT_New_Face(library, m_filename.c_str(), m_faceIndex, &m_face))
	{
		std::cout << "Could not open font " << filename << "\n";
	}

	setSize(size);
}

Font::Font(const Font& copy)
{
	m_face = copy.m_face;
	m_filename = copy.m_filename;
	m_faceIndex = copy.m_faceIndex;
	setSize(copy.m_size);
}

Font::~Font()
{
}


FT_Face Font::getFace() const
{
	return m_face;
}

long Font::getFaceIndex() const
{
	return m_faceIndex;
}

std::string Font::getFilename() const
{
	return m_filename;
}

size_t Font::getSize() const
{
	return m_size;
}


void Font::setSize(size_t value)
{
	m_size = value;

	FT_Set_Pixel_Sizes(m_face, 0, m_size);
}

bool Font::loadChar(const char c)
{
	if (FT_Load_Char(m_face, c, FT_LOAD_RENDER))
	{
		std::cout << "Could not load character " << c << "\n";
		return false;
	}

	return true;
}

FT_GlyphSlot Font::getGlyph()
{
	return m_face->glyph;
}
