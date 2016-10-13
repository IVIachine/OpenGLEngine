#include "TextField.h"
#include <sstream>
#include "EventSystem.h"
#include "Input.h"
#include <cctype>

TextField::TextField()
{
	m_isActive = false;
	m_color = Color::White;
	m_font = Font();
	m_string = "";
	m_text = Text();
	m_position = Vector2::ZERO;
}

TextField::TextField(Vector2 position, Font font, Color color)
{
	m_isActive = false;
	m_color = color;
	m_font = font;
	m_string = "";
	m_text = Text();
	m_position = position;
}

TextField::~TextField()
{
}


std::string TextField::getString()
{
	std::string tmp = m_string;

	clear();

	return tmp;
}

std::string TextField::peekString()
{
	return m_string;
}

void TextField::setString(std::string str)
{
	m_string = str;
}

void TextField::clear()
{
	setString("");
	m_text.setString(m_string);
}


bool TextField::isActive()
{
	return m_isActive;
}

void TextField::setActive(bool value)
{
	m_isActive = value;
}


void TextField::update()
{
	m_text.setFont(&m_font);
	m_text.setPosition(m_position);
	m_text.setFillColor(m_color);

	if (m_isActive)
	{
		char c = INPUT->getChar();
		if (isprint(c))
		{
			m_string += c;
		}

		if (INPUT->getKeyDown(Keyboard::Keys::BackSpace))
		{
			if (m_string.size() > 0)
			{
				m_string.erase(m_string.end() - 1, m_string.end());
			}
		}

		m_text.setString(m_string);
	}
}

void TextField::draw()
{
	GRAPHICS->draw(m_text);
}