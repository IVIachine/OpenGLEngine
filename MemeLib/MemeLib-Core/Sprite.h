#ifndef _SPRITE_H_
#define _SPRITE_H_	

#include "Vector2.h"
#include "Texture2D.h"

const float yRot = 180.f * Maths::DEG_TO_RAD;

class Sprite : public Trackable
{
public:
	Sprite() {};	
	Sprite(const Sprite& copy);
	~Sprite();

	Texture2D*	getTexture2D() const;

	Vector2		getPosition() const;
	void		setPosition(Vector2 value);

	float		getRotation() const;
	void		setRotation(float value);

	Vector2		getScale() const;
	void		setScale(Vector2 value);

	void		draw(Camera& camera);

private:
	Texture2D*	mp_texture;
	Vector2		m_position;
	Vector2		m_scale;
	float		m_rotation;

	Sprite(Texture2D* texture2D);

	friend class ResourceManager;
};

#endif