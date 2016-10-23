#ifndef _COLOR_H_
#define _COLOR_H_

#include <Trackable.h>

typedef unsigned char byte;

class Color : public Trackable
{
public:
	Color();
	Color(const Color& copy);
	Color(byte r, byte g, byte b, byte a = 255);
	~Color();

	static const Color Black;
	static const Color White;
	static const Color Red;
	static const Color Green;
	static const Color Blue;
	static const Color Yellow;
	static const Color Magenta;
	static const Color Cyan;
	static const Color Clear;

	friend bool operator==(const Color& lhs, const Color& rhs);
	friend bool operator!=(const Color& lhs, const Color& rhs);
	friend Color operator+(const Color& lhs, const Color& rhs);
	friend Color operator*(const Color& lhs, const Color& rhs);
	friend Color& operator+=(Color& lhs, const Color& rhs);
	friend Color& operator*=(Color& lhs, const Color& rhs);

	byte r, g, b, a;
};

#endif