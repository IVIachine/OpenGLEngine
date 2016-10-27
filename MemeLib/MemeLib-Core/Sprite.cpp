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


_vec3 Sprite::getPosition() const
{
	return m_position;
}

void Sprite::setPosition(_vec3 value)
{
	m_position = value;
}


_vec3 Sprite::getRotation() const
{
	return m_rotation;
}

void Sprite::setRotation(_vec3 value)
{
	m_rotation = value;
}


_vec3 Sprite::getScale() const
{
	return m_scale;
}

void Sprite::setScale(_vec3 value)
{
	m_scale = value;
}


void Sprite::draw(Camera& camera)
{
	// set position
	mp_texture->transform().setPos(m_position);

	// set rotation
	mp_texture->transform().setRot(m_rotation);

	// set scale
	mp_texture->transform().setScale(m_scale);

	// draw
	mp_texture->draw(camera);
}
