#include "Sprite.h"
#include "Texture2D.h"
#include "Graphics.h"


Sprite::Sprite(Texture2D* texture2D)
{
	mp_texture = texture2D;
}

Sprite::Sprite(const Sprite& copy)
{
	mp_texture = copy.mp_texture;
	m_position = copy.m_position;
	m_rotation = copy.m_rotation;
	m_scale = copy.m_scale;
}

Sprite::~Sprite()
{
}


Texture2D* Sprite::getTexture2D() const
{ 
	return mp_texture; 
}


Vector2 Sprite::getPosition() const
{
	return m_position;
}

void Sprite::setPosition(Vector2 value)
{
	m_position = value;
}


float Sprite::getRotation() const
{
	return m_rotation;
}

void Sprite::setRotation(float value)
{
	m_rotation = value;
}


Vector2 Sprite::getScale() const
{
	return m_scale;
}

void Sprite::setScale(Vector2 value)
{
	m_scale = value;
}


void Sprite::draw(Camera& camera)
{
	// set position
	mp_texture->transform().setPos({ m_position.x, m_position.y, 0.f });

	// set rotation
	mp_texture->transform().setRot({ 0.f, yRot, m_rotation });

	// set scale
	mp_texture->transform().setScale({ m_scale.x, m_scale.y, 1.f });

	// draw
	mp_texture->draw(camera);
}
