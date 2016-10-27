#ifndef _SPRITE_H_
#define _SPRITE_H_	

#include "Vector3.h"
#include "Texture2D.h"

const float yRot = 180.f * Maths::DEG_TO_RAD;

class Sprite : public Trackable
{
public:
	Sprite() {};	
	Sprite(const Sprite& copy);
	~Sprite();

	Texture2D*	getTexture2D() const;

	_vec3		getPosition() const;
	void		setPosition(_vec3 value);

	_vec3		getRotation() const;
	void		setRotation(_vec3 value);

	_vec3		getScale() const;
	void		setScale(_vec3 value);

	void		draw(Camera& camera);

private:
	Texture2D*	mp_texture;
	_vec3		m_position;
	_vec3		m_scale;
	_vec3		m_rotation;

	Sprite(Texture2D* texture2D);

	friend class ResourceManager;
};

#endif