#include "Vector2.h"


/*	Constructors
* * * * * * * * * * * * */
Vector2::Vector2()
{
	x = 0.0f;
	y = 0.0f;
}

Vector2::Vector2(float x, float y) : x(x), y(y)
{
}

Vector2::Vector2(const Vector2& copy) : x(copy.x), y(copy.y)
{
}

Vector2::~Vector2()
{
}


/*	Functions
* * * * * * * * * * * * */
float Vector2::getX() const
{
	return x;
}

float Vector2::getY() const
{
	return y;
}

void Vector2::setX(float value)
{
	x = value;
}

void Vector2::setY(float value)
{
	y = value;
}


float Vector2::magnitude()
{
	float magSquared = sqaredMagnitude();
	return sqrtf(magSquared);
}

float Vector2::sqaredMagnitude()
{
	return (x * x) + (y * y);
}


void Vector2::normalize()
{
	float invLength = 1.0f / (magnitude() + FLT_MIN);
	x *= invLength;
	y *= invLength;
}

Vector2 Vector2::normalized()
{
	Vector2 out = *(this);
	out.normalize();
	return out;
}


/*	Constants
* * * * * * * * * * * * */
const Vector2 Vector2::ZERO = Vector2(0.0f, 0.0f);
const Vector2 Vector2::ONE = Vector2(1.0f, 1.0f);
const Vector2 Vector2::UP = Vector2(0.0f, -1.0f);
const Vector2 Vector2::DOWN = Vector2(0.0f, 1.0f);
const Vector2 Vector2::LEFT = Vector2(-1.0f, 0.0f);
const Vector2 Vector2::RIGHT = Vector2(1.0f, 0.0f);


/*	Static Functions
* * * * * * * * * * * * */
float Vector2::angle(const Vector2& from, const Vector2& to)
{
	//float _det = Vector2::det(Vector2::RIGHT, to);
	//float _dot = Vector2::dot(Vector2::RIGHT, to);
	//return atan2(_det, _dot) - from

	Vector2 d = (to - from);
	return atan2(d.y, d.x);
}

float Vector2::det(const Vector2& a, const Vector2& b)
{
	return (a.x * b.y) - (a.y * b.x);
}

float Vector2::distance(const Vector2& a, const Vector2& b)
{
	float dx = powf((b.x - a.x), 2);
	float dy = powf((b.y - a.y), 2);

	return sqrtf(dx + dy);
}

float Vector2::dot(const Vector2& a, const Vector2& b)
{
	return (a.x * b.x) + (a.y * b.y);
}


Vector2 Vector2::angle(float angle)
{
	return Vector2(cos(angle), sin(angle));
}

Vector2 Vector2::direction(const Vector2& from, const Vector2& to)
{
	return (to - from).normalized();
}

Vector2 Vector2::lengthDir(const float length, const float dir)
{
	float ldx = (length * cos(dir));
	float ldy = (length * sin(dir));

	return Vector2(ldx, ldy);
}

Vector2 Vector2::lerp(const Vector2& a, const Vector2& b, float t)
{
	if (t <= 0.f)
	{
		return a;
	}
	else if (t >= 1.f)
	{
		return b;
	}

	return a * t + b * (1.f - t);
}

Vector2 Vector2::moveTowards(const Vector2& a, const Vector2& b, float t)
{
	return lerp(a, b, t);
}

Vector2 Vector2::reflect(const Vector2& direction, const Vector2& normal)
{
	return (normal - direction) * (2.f * dot(direction, normal));
}

Vector2 Vector2::scale(const Vector2& a, const Vector2& b)
{
	return Vector2(a.x * b.x, a.y * b.y);
}


/*	Operator Overloads
* * * * * * * * * * * * */
std::ostream& operator<<(std::ostream& out, const Vector2& v)
{
	// (x, y)

	out << "(" << v.x << ", " << v.y << ")";

	return out;
}

std::istream& operator>>(std::istream& in, Vector2& v)
{
	in >> v.x >> v.y;

	return in;
}


bool operator!=(const Vector2& lhs, const Vector2& rhs)
{
	return (lhs.x != rhs.x) || (lhs.y != rhs.y);
}

bool operator==(const Vector2& lhs, const Vector2& rhs)
{
	return (lhs.x == rhs.x) && (lhs.y == rhs.y);
}


Vector2 operator+(const Vector2& lhs, const Vector2& rhs)
{
	return Vector2(lhs.x + rhs.x, lhs.y + rhs.y);
}

Vector2& operator+=(Vector2& lhs, const Vector2& rhs)
{
	lhs.x += rhs.x;
	lhs.y += rhs.y;

	return lhs;
}


Vector2 operator-(const Vector2& lhs, const Vector2& rhs)
{
	return Vector2(lhs.x - rhs.x, lhs.y - rhs.y);
}

Vector2& operator-=(Vector2& lhs, const Vector2& rhs)
{
	lhs.x -= rhs.x;
	lhs.y -= rhs.y;

	return lhs;
}


Vector2 operator*(const Vector2& lhs, const float rhs)
{
	return Vector2(lhs.x * rhs, lhs.y * rhs);
}

Vector2& operator*=(Vector2& lhs, const float rhs)
{
	lhs.x *= rhs;
	lhs.y *= rhs;

	return lhs;
}


Vector2 operator/(const Vector2& lhs, const float rhs)
{
	return Vector2(lhs.x / rhs, lhs.y / rhs);
}

Vector2& operator/=(Vector2& lhs, const float rhs)
{
	lhs.x /= rhs;
	lhs.y /= rhs;

	return lhs;
}