#include "Text.h"

Text::Text()
{
	mText_sf = sf::Text();
	mFont = NULL;
	mString = "";
	mSize = 12;
}

Text::Text(const Text& copy)
{
	mFont = copy.mFont;
	mString = copy.mString;
	mSize = copy.mSize;
	mStyle = copy.mStyle;
	mColor = copy.mColor;
	mPosition = copy.mPosition;
}

Text::Text(Font* fnt, std::string str, size_t size, Text::Style style, Color color, Vector2 pos)
{
	mFont = fnt;
	mString = str;
	mSize = size;
	mStyle = style;
	mColor = color;
	mPosition = pos;
}

Text::~Text()
{
	
}


void Text::setFont(Font* font)
{
	mFont = font;
	mText_sf.setFont(mFont->m_sf_font);
}

void Text::setString(std::string str)
{
	mString = str;
	mText_sf.setString(mString);
}

void Text::setSize(size_t size)
{
	mSize = size;
	mText_sf.setCharacterSize(mSize);
}

void Text::setStyle(Text::Style style)
{
	mStyle = style;

	mText_sf.setStyle((sf::Text::Style)mStyle);
}

void Text::setFillColor(Color color)
{
	mColor = color;

	sf::Color tmp(mColor.r, mColor.g, mColor.b, mColor.a);

	mText_sf.setFillColor(tmp);
}


Font* Text::getFont()
{
	return mFont;
}

std::string Text::getString()
{
	return mString;
}

size_t Text::getSize()
{
	return mSize;
}

Text::Style Text::getStyle()
{
	return mStyle;
}

Color Text::getColor()
{
	return mColor;
}


void Text::setPosition(Vector2 pos)
{
	mPosition = pos;
	mText_sf.setPosition(mPosition.x, mPosition.y);
}

void Text::setScale(Vector2 scale)
{
	mScale = scale;
	mText_sf.setScale(mScale.x, mScale.y);
}

void Text::setOrigin(Vector2 origin)
{
	mOrigin = origin;
	mText_sf.setOrigin(mOrigin.x, mOrigin.y);
}

void Text::setRotation(float angle)
{
	mRotation = angle;
	mText_sf.setRotation(mRotation);
}


Vector2 Text::getPosition()
{
	return mPosition;
}

Vector2 Text::getScale()
{
	return mScale;
}

Vector2 Text::getOrigin()
{
	return mOrigin;
}

float Text::getRotation()
{
	return mRotation;
}


float Text::width()
{
	return mText_sf.getLocalBounds().width;
}

float Text::height()
{
	return mText_sf.getLocalBounds().height;
}

Vector2 Text::size()
{
	return Vector2(width(), height());
}