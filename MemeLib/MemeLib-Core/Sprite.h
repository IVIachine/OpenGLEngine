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

	Vec3		getPosition() const;
	void		setPosition(Vec3 value);

	Vec3		getRotation() const;
	void		setRotation(Vec3 value);
	void		setYRotation(float value);

	Vec3		getScale() const;
	void		setScale(Vec3 value);

	void		draw(Camera& camera);
	void		setFacing(float face) { mFacing = face; };
	float		getFacing()const { return mFacing; };
private:
	Texture2D*	mp_texture;
	Vec3		m_position;
	Vec3		m_scale;
	Vec3		m_rotation;
	float		mFacing;
	Sprite(Texture2D* texture2D);

	friend class ResourceManager;
};

#endif