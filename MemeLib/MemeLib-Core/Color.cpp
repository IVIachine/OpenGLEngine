#include "Color.h"

Color::Color()
{
	r = 0;
	g = 0;
	b = 0;
	a = 255;
}

Color::Color(const Color& copy)
{
	r = copy.r;
	g = copy.g;
	b = copy.b;
	a = copy.a;
}

Color::Color(byte r, byte g, byte b, byte a)
{
	this->r = r;
	this->g = g;
	this->b = b;
	this->a = a;
}

Color::~Color()
{

}

const Color Color::Black = Color(0, 0, 0);
const Color Color::White = Color(255, 255, 255);
const Color Color::Red = Color(255, 0, 0);
const Color Color::Green = Color(0, 255, 0);
const Color Color::Blue = Color(0, 0, 255);
const Color Color::Yellow = Color(255, 255, 0);
const Color Color::Magenta = Color(255, 0, 255);
const Color Color::Cyan = Color(0, 255, 255);
const Color Color::Clear = Color(0, 0, 0, 0);

bool operator==(const Color& lhs, const Color& rhs)
{
	return
		lhs.r == rhs.r &&
		lhs.g == rhs.g &&
		lhs.b == rhs.b &&
		lhs.a == rhs.a;
}

bool operator!=(const Color& lhs, const Color& rhs)
{
	return
		lhs.r != rhs.r &&
		lhs.g != rhs.g &&
		lhs.b != rhs.b &&
		lhs.a != rhs.a;
}

Color operator+(const Color& lhs, const Color& rhs)
{
	return Color(lhs.r + rhs.r, lhs.g + rhs.g, lhs.b + rhs.b, lhs.a + rhs.a);
}

Color operator*(const Color& lhs, const Color& rhs)
{
	return Color(lhs.r * rhs.r, lhs.g * rhs.g, lhs.b * rhs.b, lhs.a * rhs.a);
}

Color& operator+=(Color& lhs, const Color& rhs)
{
	lhs.r += rhs.r;
	lhs.g += rhs.g;
	lhs.b += rhs.b;
	lhs.a += rhs.a;

	return lhs;
}

Color& operator*=(Color& lhs, const Color& rhs)
{
	lhs.r *= rhs.r;
	lhs.g *= rhs.g;
	lhs.b *= rhs.b;
	lhs.a *= rhs.a;

	return lhs;
}