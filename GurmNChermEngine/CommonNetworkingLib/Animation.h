#ifndef _ANIMATION_H_
#define _ANIMATION_H_

#include <vector>
#include "Sprite.h"

class Animation
{
public:
	Animation();
	Animation(std::string name, int theSpeed);
	~Animation();

	void addSprite(Texture2D* texture2D, int rows, int cols, Vector2 size, int speed, Vector2 offset, Vector2 scale);

	Sprite			getCurrentSprite();
	std::string		getName();
	virtual void	update();

private:
	std::vector<Sprite> mSprites;
	std::string	m_name;
	float		m_timer;
	int			m_speed;
	int			m_index;	
	int			m_count;
};

#endif // !_ANIMATION_H_
