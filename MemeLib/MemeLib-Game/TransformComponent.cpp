#include "TransformCOmponent.h"
#include "Game.h"
#include "Graphics.h"

void TransformComponent::wrapCoords()
{
	if (m_wrap)
	{
		float width = (float)GRAPHICS->getWidth();
		float height = (float)GRAPHICS->getHeight();

		float x = m_data.position.getX();
		float y = m_data.position.getY();

		if (x < 0.0f)
		{
			m_data.position.setX(width);
		}
		else if (x > width)
		{
			m_data.position.setX(0.0f);
		}

		if (y < 0.0f)
		{
			m_data.position.setY(height);
		}
		else if (y > height)
		{
			m_data.position.setY(0.0f);
		}
	}
}


Vector2 TransformComponent::forward() const
{
	return Vector2::lengthDir(1.0f, getRotation());
}

Vector2 TransformComponent::backward() const
{
	return Vector2::lengthDir(1.0f, getRotation() + Maths::PI);
}

Vector2 TransformComponent::left() const
{
	return Vector2::lengthDir(1.0f, getRotation() - (Maths::PI / 2.0f));
}

Vector2 TransformComponent::right() const
{
	return Vector2::lengthDir(1.0f, getRotation() + (Maths::PI / 2.0f));
}