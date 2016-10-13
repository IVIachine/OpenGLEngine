#ifndef _TEXT_H_
#define _TEXT_H_

#include "Font.h"
#include "Color.h"
#include "Vector2.h"

class Graphics;

class Text
{
public:
	enum Style
	{
		Regular = 0,
		Bold = 1 << 0,
		Italic = 1 << 1,
		Underlined = 1 << 2
	};

	Text();
	Text(const Text& copy);
	Text(
		Font* fnt, 
		std::string str, 
		size_t size,
		Style style = Style::Regular,
		Color color = Color::White,
		Vector2 pos = Vector2::ZERO);
	~Text();

	friend class Graphics;

	void		setFont(Font* font);
	void		setString(std::string str);
	void		setSize(size_t size);
	void		setStyle(Style style);
	void		setFillColor(Color color);

	Font*		getFont();
	std::string getString();
	size_t		getSize();
	Style		getStyle();
	Color		getColor();
	
	void		setPosition(Vector2 position);
	void		setScale(Vector2 scale);
	void		setOrigin(Vector2 origin);
	void		setRotation(float angle);

	Vector2		getPosition();
	Vector2		getScale();
	Vector2		getOrigin();
	float		getRotation();
	
	float		width();
	float		height();
	Vector2		size();

private:
	sf::Text mText_sf;

	Font*			mFont;
	std::string		mString;
	unsigned int	mSize;
	Style			mStyle;
	Color			mColor;

	Vector2
		mPosition,
		mScale,
		mOrigin;

	float mRotation;

};

#endif