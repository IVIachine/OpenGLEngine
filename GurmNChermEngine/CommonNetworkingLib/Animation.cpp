#include "Animation.h"

Animation::Animation()
{
}

Animation::Animation(std::string name, int msPerCel)
{
	m_speed = msPerCel;	
	m_index = 0;
	m_name = name;
	m_timer = 0;
	m_count = 0;
}

Animation::~Animation()
{
}


void Animation::addSprite(Texture2D* texture2D, int rows, int cols, Vector2 size, int speed, Vector2 offset, Vector2 scale)
{
	m_speed = speed;

	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)
		{
			mSprites.push_back(Sprite(*texture2D));
		}
	}

	m_timer = 0;
	m_count = rows * cols;
	m_index = 0;
}

Sprite Animation::getCurrentSprite()
{
	return mSprites[m_index];
}

std::string Animation::getName()
{
	return m_name;
}

void Animation::update()
{
	m_timer += 1;

	if (m_timer >= m_speed)
	{
		if (m_index + 1 == m_count)
		{
			m_index = 0;
		}
		else
		{
			m_index++;
		}

		m_timer = 0;
	}
}