#ifndef _TEXT_FIELD_H_
#define _TEXT_FIELD_H_

#include "Graphics.h"

class TextField
{
public:
	TextField();
	TextField(Vector2 position, Font font, Color color);
	~TextField();

	std::string getString();
	std::string peekString();
	void		setString(std::string str);
	void		clear();

	bool		isActive();
	void		setActive(bool value);

	size_t		size() const { return m_string.size(); }

	void		update();
	void		draw();

private:
	bool		m_isActive;
	Color		m_color;
	Font		m_font;
	std::string m_string;
	Text		m_text;
	Vector2		m_position;
};

#endif // !_TEXT_FIELD_H_
