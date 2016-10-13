#include "Sprite.h"

Sprite::Sprite()
{
	setPosition(Vector2::ZERO);
	setOrigin(Vector2::ZERO);
	setScale(Vector2::ONE);
	setRotation(0.0f);
	setColor(Color::White);
}

Sprite::Sprite(Texture2D texture, Vector2 pos)
{
	setTexture(texture);
	
	setPosition(pos);
	setOrigin(Vector2::ZERO);
	setScale(Vector2::ONE);
	setRotation(0.0f);
	setColor(Color::White);
}

Sprite::Sprite(const Sprite& copy)
{
	setTexture(copy.m_texture2D);

	setPosition(copy.m_position);
	setOrigin(copy.m_origin);
	setScale(copy.m_scale);
	setRotation(copy.m_rotation);
	setColor(copy.m_color);
}

Sprite::~Sprite()
{
	//delete mTexture;
}


Texture2D* Sprite::getTexture()
{
	return &m_texture2D;
}

void Sprite::setTexture(Texture2D texture)
{
	m_texture2D = Texture2D(texture);
	m_sf_sprite.setTexture(m_texture2D.m_sf_texture);
}


Vector2 Sprite::getOrigin()
{
	return m_origin;
}

void Sprite::setOrigin(Vector2 origin)
{
	m_origin = origin;
	m_sf_sprite.setOrigin(m_origin.x, m_origin.y);
}


Vector2 Sprite::getPosition()
{
	return m_position;
}

void Sprite::setPosition(Vector2 pos)
{
	m_position = pos;
	m_sf_sprite.setPosition(m_position.x, m_position.y);
}


Vector2 Sprite::getScale()
{
	return m_scale;
}

void Sprite::setScale(Vector2 scale)
{
	m_scale = scale;
	m_sf_sprite.setScale(m_scale.x, m_scale.y);
}


float Sprite::getRotation()
{
	return m_rotation;
}

void Sprite::setRotation(float angle)
{
	m_rotation = angle;
	m_sf_sprite.setRotation(m_rotation);
}


Color Sprite::getColor()
{
	return m_color;
}

void Sprite::setColor(Color color)
{
	m_color = color;

	m_sf_sprite.setColor({ 
		m_color.r, 
		m_color.g, 
		m_color.b, 
		m_color.a });
}