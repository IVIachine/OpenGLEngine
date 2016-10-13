#ifndef _SPRITE_H_
#define _SPRITE_H_

#include "Color.h"
#include "Texture2D.h"

class Graphics;

class Sprite
{
public:
	Sprite();
	Sprite(Texture2D texture, Vector2 pos = Vector2::ZERO);
	Sprite(const Sprite& copy);
	~Sprite();

	friend class Graphics;

	Texture2D*	getTexture();
	void		setTexture(Texture2D texture);

	Vector2		getOrigin();
	void		setOrigin(Vector2 origin);

	Vector2		getPosition();
	void		setPosition(Vector2 pos);

	Vector2		getScale();
	void		setScale(Vector2 scale);

	float		getRotation();
	void		setRotation(float angle);

	Color		getColor();
	void		setColor(Color c);

private:
	Texture2D	m_texture2D;
	Vector2		m_origin;
	Vector2		m_position;
	Vector2		m_scale;
	float		m_rotation;
	Color		m_color;

	sf::Sprite m_sf_sprite;
};

#endif