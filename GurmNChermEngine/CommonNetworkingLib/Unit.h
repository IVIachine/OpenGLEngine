#ifndef _UNIT_H_
#define _UNIT_H_

#include "Animation.h"
#include "Graphics.h"

class Unit
{
public:
	Unit(Animation& anim, Vector2 pos, Vector2 size, Vector2 scale);
	~Unit();

	Animation*	getAnimation();
	Vector2		getPosition();
	Vector2		getSize();
	
	void		setAnimation(Animation *anim);
	void		setPosition(Vector2 position);
	void		setScale(Vector2 scale);
	void		setSize(Vector2 size);

	virtual void update();
	virtual void draw();

private:
	Animation	m_animation;
	Vector2		m_position;
	Vector2		m_scale;
	Vector2		m_size;

	friend class UnitManager;
};

#endif