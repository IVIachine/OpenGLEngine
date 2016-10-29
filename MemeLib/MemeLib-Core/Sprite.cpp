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


Vec3 Sprite::getPosition() const
{
	return m_position;
}

void Sprite::setPosition(Vec3 value)
{
	m_position = value;
}


Vec3 Sprite::getRotation() const
{
	return m_rotation;
}

void Sprite::setRotation(Vec3 value)
{
	m_rotation = value;
}

void Sprite::setYRotation(float value)
{
	setRotation(Vec3(getRotation().x, -value, getRotation().z));
}



Vec3 Sprite::getScale() const
{
	return m_scale;
}

void Sprite::setScale(Vec3 value)
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
