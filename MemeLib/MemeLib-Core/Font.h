#ifndef _FONT_H_
#define _FONT_H_

#include <string>
#include <Trackable.h>

class Font : public Trackable
{
public:
	Font();
	Font(const Font& copy);
	~Font();

private:
	Font(const std::string& filename);

	std::string m_filename;

	friend class ResourceManager;
};

#endif // !_FONT_H_
