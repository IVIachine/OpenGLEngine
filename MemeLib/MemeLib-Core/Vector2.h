#ifndef _VECTOR2_H_
#define _VECTOR2_H_

#include <glm.hpp>
#include <functional>
#include <iostream>
#include <Trackable.h>
#include "Maths.h"

typedef glm::vec2 _vec2;
class Vector2 : public Trackable
{
public:
	/*	Constructors
	* * * * * * * * * * * * */
	Vector2();
	Vector2(float x, float y);
	Vector2(const Vector2 &copy);
	~Vector2();

	/*	Variables
	* * * * * * * * * * * * */
	float x;
	float y;

	/*	Functions
	* * * * * * * * * * * * */
	float	getX() const;
	float	getY() const;

	void	setX(float value);
	void	setY(float value);

	float	magnitude();
	float	sqaredMagnitude();

	void	normalize();
	Vector2 normalized();


	/*	Constants
	* * * * * * * * * * * * */
	static const Vector2 ZERO;
	static const Vector2 ONE;
	static const Vector2 UP;
	static const Vector2 DOWN;
	static const Vector2 LEFT;
	static const Vector2 RIGHT;


	/*	Static Functions
	* * * * * * * * * * * * */
	static float	angle(const Vector2& from, const Vector2& to);
	static float	det(const Vector2& a, const Vector2& b);
	static float	distance(const Vector2& a, const Vector2& b);
	static float	dot(const Vector2& a, const Vector2& b);

	static Vector2	angle(float angle);
	static Vector2	direction(const Vector2& from, const Vector2& to);
	static Vector2	lengthDir(const float length, const float dir);
	static Vector2	lerp(const Vector2& a, const Vector2& b, float t);
	static Vector2	moveTowards(const Vector2& a, const Vector2& b, float t);
	static Vector2	reflect(const Vector2& direction, const Vector2& normal);
	static Vector2	scale(const Vector2& a, const Vector2& b);


	/*	Operator Overloads
	* * * * * * * * * * * * */
	friend std::ostream& operator<<(std::ostream& out, const Vector2& v);
	friend std::istream& operator >> (std::istream& in, Vector2& v);


	friend bool operator!=(const Vector2& lhs, const Vector2& rhs);
	friend bool operator==(const Vector2& lhs, const Vector2& rhs);


	friend Vector2 operator+(const Vector2& lhs, const Vector2& rhs);
	friend Vector2& operator+=(Vector2& lhs, const Vector2& rhs);


	friend Vector2 operator-(const Vector2& lhs, const Vector2& rhs);
	friend Vector2& operator-=(Vector2& lhs, const Vector2& rhs);


	friend Vector2 operator*(const Vector2& lhs, const float rhs);
	friend Vector2& operator*=(Vector2& lhs, const float rhs);


	friend Vector2 operator/(const Vector2& lhs, const float rhs);
	friend Vector2& operator/=(Vector2& lhs, const float rhs);
};

#endif // !_VECTOR_2_H_
