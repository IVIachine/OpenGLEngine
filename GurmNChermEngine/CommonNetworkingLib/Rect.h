#ifndef _RECT_H_
#define _RECT_H_

#include "Vector2.h"

class Rect
{
public:
	Rect();
	Rect(const Rect& copy);
	Rect(float x, float y, float w, float h);
	Rect(Vector2 pos, Vector2 size);
	Rect(Vector2 size);
	~Rect();

	static const Rect Empty;

	Vector2& position();
	Vector2& size();

	float	top();
	float	bottom();
	float	left();
	float	right();

	float	width();
	float	height();

	Vector2 getCenter();
	void	setCenter(Vector2 v);

	bool	contains(float x, float y);
	bool	contains(Vector2& v);

	static bool intersects(int ax, int ay, int aw, int ah, int bx, int by, int bw, int bh);
	static bool intersects(Rect& RectA, Rect& RectB);
	bool		intersects(Rect& r);

private:
	Vector2 m_position;
	Vector2 m_size;
};

#endif