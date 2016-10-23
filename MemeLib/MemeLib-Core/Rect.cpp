#include "Rect.h"
#include "Vector2.h"

/*	Constructors
* * * * * * * * * * * * */
Rect::Rect()
{
	x = 0.f;
	y = 0.f;
	width = 0.f;
	height = 0.f;
}

Rect::Rect(float x, float y, float width, float height) :
	x(x), y(y), width(width), height(height)
{
}

Rect::Rect(Vector2 position, Vector2 size) :
	x(position.x), y(position.y), width(size.x), height(size.y)
{
}

Rect::Rect(const Rect& copy)
{
	x = copy.x;
	y = copy.y;
	width = copy.width;
	height = copy.height;
}

Rect::~Rect()
{
}


/*	Static Functions
* * * * * * * * * * * * */
Rect Rect::minMaxRect(Vector2 min, Vector2 max)
{
	Rect rect(0, 0, 0, 0);
	rect.setMin(min);
	rect.setMax(max);

	return rect;
}


/*	Functions
* * * * * * * * * * * * */
Vector2 Rect::getCenter() const
{
	return getPosition() + (getSize() * 0.5f);
}

Vector2 Rect::getMax() const
{
	return Vector2(getXMax(), getYMax());
}

Vector2 Rect::getMin() const
{
	return Vector2(getXMin(), getYMin());
}

Vector2 Rect::getPosition() const
{
	return Vector2(x, y);
}

Vector2 Rect::getSize() const
{
	return Vector2(width, height);
}


float Rect::getXMax() const
{
	return x + width;
}

float Rect::getYMax() const
{
	return y + height;
}

float Rect::getXMin() const
{
	return x;
}

float Rect::getYMin() const
{
	return y;
}


void Rect::setCenter(Vector2 pos)
{
	setPosition(pos - (getSize() * 0.5f));
}

void Rect::setMax(Vector2 pos)
{
	Vector2 d = pos - getMax();
	width += d.x;
	height += d.y;
}

void Rect::setMin(Vector2 pos)
{
	Vector2 d = pos - getMin();
	x += d.x;
	y += d.y;
	width -= d.x;
	height -= d.y;
}

void Rect::setPosition(Vector2 pos)
{
	x = pos.x;
	y = pos.y;
}

void Rect::setSize(Vector2 size)
{
	width = size.x;
	height = size.y;
}


void Rect::setXMax(float value)
{
	setMax(Vector2(value, getYMax()));
}

void Rect::setYMax(float value)
{
	setMax(Vector2(getXMax(), value));
}

void Rect::setXMin(float value)
{
	setMin(Vector2(value, getYMin()));
}

void Rect::setYMin(float value)
{
	setMin(Vector2(getXMin(), value));
}


bool Rect::contains(Vector2 pos)
{
	return
		pos.x >= getXMin() &&
		pos.y >= getYMin() &&
		pos.x <= getXMax() &&
		pos.y <= getYMax();
}

bool Rect::overlaps(Rect rect)
{
	return contains(rect.getMin()) || contains(rect.getMax());
}


/*	Operator Overloads
* * * * * * * * * * * * */
std::ostream& operator<<(std::ostream& out, const Rect& r)
{
	// (x, y, w, h)

	out << "(" << r.x << ", " << r.y << ", " << r.width << ", " << r.height << ")";

	return out;
}

std::istream& operator >> (std::istream& in, Rect& r)
{
	in >> r.x >> r.y >> r.width >> r.height;

	return in;
}


bool operator!=(const Rect& lhs, const Rect& rhs)
{
	return
		lhs.x != rhs.x ||
		lhs.y != rhs.y ||
		lhs.width != rhs.width ||
		lhs.height != rhs.height;
}

bool operator==(const Rect& lhs, const Rect& rhs)
{
	return
		lhs.x == rhs.x &&
		lhs.y == rhs.y &&
		lhs.width == rhs.width &&
		lhs.height == rhs.height;
}