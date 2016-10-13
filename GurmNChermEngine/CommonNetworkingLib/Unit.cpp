#include "Unit.h"
#include "Graphics.h"

Unit::Unit(Animation& anim, Vector2 pos, Vector2 size, Vector2 scale)
{
	setAnimation(&anim);
	setPosition(pos);
	setScale(scale);
	setSize(size);
}

Unit::~Unit()
{

}


Animation* Unit::getAnimation()
{
	return &m_animation;
}

Vector2 Unit::getPosition()
{
	return m_position;
}

Vector2 Unit::getSize()
{
	return m_size;
}


void Unit::setAnimation(Animation* anim)
{
	m_animation = *anim;
}

void Unit::setPosition(Vector2 position)
{
	m_position = position;
}

void Unit::setScale(Vector2 scale)
{
	m_scale = scale;
}

void Unit::setSize(Vector2 size)
{
	m_size = size;
}


void Unit::update()
{
	m_animation.update();
}

void Unit::draw()
{
	//GRAPHICS->drawSprite(m_animation.getCurrentSprite(), m_pos.x, m_pos.y);
	GRAPHICS->draw(m_animation.getCurrentSprite());
}
