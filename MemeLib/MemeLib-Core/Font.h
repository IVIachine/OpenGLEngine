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

	std::string	getFilename() const;

private:
	Font(std::string filename);

	std::string	m_filename;

	friend class ResourceManager;
};

#endif // !_FONT_H_
