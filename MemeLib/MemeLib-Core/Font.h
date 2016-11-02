#ifndef _FONT_H_
#define _FONT_H_

#include <string>
#include <Trackable.h>

#include <ft2build.h>
#include FT_FREETYPE_H

class Font : public Trackable
{
public:
	Font();
	Font(const Font& copy);
	~Font();

	FT_Face		getFace() const;
	long		getFaceIndex() const;
	std::string	getFilename() const;
	size_t		getSize() const;
	
	void		setSize(size_t value);

	bool		loadChar(const char c);

	FT_GlyphSlot	getGlyph();

private:
	Font(FT_Library library, std::string filename, size_t size = 12, long faceIndex = 0);

	FT_Face		m_face;
	std::string	m_filename;
	long		m_faceIndex;
	size_t		m_size;

	friend class ResourceManager;
};

#endif // !_FONT_H_
