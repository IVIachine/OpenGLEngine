#include "Rect.h"

Rect::Rect()
{

}

Rect::Rect(const Rect& copy)
{
	m_position = copy.m_position;
	m_size = copy.m_size;
}

Rect::Rect(float x, float y, float w, float h)
{
	m_position = Vector2(x, y);
	m_size = Vector2(w, h);
}

Rect::Rect(Vector2 pos, Vector2 size)
{
	m_position = pos;
	m_size = size;
}

Rect::Rect(Vector2 size)
{
	m_position = Vector2::ZERO;
	m_size = size;
}

Rect::~Rect()
{

}


const Rect Rect::Empty = Rect(0, 0, 0, 0);


Vector2& Rect::position()
{
	return m_position;
}

Vector2& Rect::size()
{
	return m_size;
}


float Rect::top()
{
	return m_position.y;
}

float Rect::bottom()
{
	return m_position.y + m_size.y;
}

float Rect::left()
{
	return m_position.x;
}

float Rect::right()
{
	return m_position.x + m_size.x;
}

float Rect::width()
{
	return m_size.x;
}

float Rect::height()
{
	return m_size.y;
}


Vector2 Rect::getCenter()
{
	return m_position + (m_size * 0.5f);
}

void Rect::setCenter(Vector2 v)
{
	m_position = v - (m_size * 0.5f);
}


bool Rect::contains(float x, float y)
{
	float
		mx = m_position.x,
		my = m_position.y,
		mw = m_position.x + m_size.x,
		mh = m_position.y + m_size.y;

	return x > mx && x < mw && y > my && y < mh;
}

bool Rect::contains(Vector2& v)
{
	float 
		mx = m_position.x,
		my = m_position.y,
		mw = m_position.x + m_size.x,
		mh = m_position.y + m_size.y;

	return v.x > mx && v.x < mw && v.y > my && v.y < mh;
}


bool Rect::intersects(int ax, int ay, int aw, int ah, int bx, int by, int bw, int bh)
{
	auto inRange = [](auto value, auto min, auto max)
	{
		return (value >= min) && (value <= max);
	};

	bool xOverlap = inRange(ax, bx, bx + bw) || inRange(bx, ax, ax + aw);
	bool yOverlap = inRange(ay, by, by + bh) || inRange(by, ay, ay + ah);

	return xOverlap && yOverlap;
}

bool Rect::intersects(Rect& a, Rect& b)
{
	int ax = (int)a.position().x;
	int ay = (int)a.position().y;
	int aw = (int)a.width();
	int ah = (int)a.height();

	int bx = (int)b.position().x;
	int by = (int)b.position().y;
	int bw = (int)b.width();
	int bh = (int)b.height();

	return intersects(ax, ay, aw, ah, bx, by, bw, bh);
}

bool Rect::intersects(Rect& other)
{
	return Rect::intersects(*this, other);
}