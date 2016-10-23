#include "Vector3.h"
#include <glm.hpp>


/*	Constructors
* * * * * * * * * * * * */
Vector3::Vector3()
{
	x = 0.0f;
	y = 0.0f;
	z = 0.0f;
}

Vector3::Vector3(float x, float y, float z) : x(x), y(y), z(z)
{
}

Vector3::Vector3(const Vector3& rhs) : x(rhs.x), y(rhs.y), z(rhs.z)
{
}

Vector3::~Vector3()
{
}


/*	Functions
* * * * * * * * * * * * */
float Vector3::getX() const
{
	return x;
}

float Vector3::getY() const
{
	return y;
}

float Vector3::getZ() const
{
	return z;
}


void Vector3::setX(float value)
{
	x = value;
}

void Vector3::setY(float value)
{
	y = value;
}

void Vector3::setZ(float value)
{
	z = value;
}


float Vector3::magnitude()
{
	float magSquared = sqaredMagnitude();
	return sqrtf(magSquared);
}

float Vector3::sqaredMagnitude()
{
	return (x * x) + (y * y) + (z * z);
}


void Vector3::normalize()
{
	float invLength = 1.0f / (magnitude() + FLT_MIN);
	x *= invLength;
	y *= invLength;
	z *= invLength;
}

Vector3 Vector3::normalized()
{
	Vector3 out = *(this);
	out.normalize();
	return out;
}


/*	Constants
* * * * * * * * * * * * */
const Vector3 Vector3::ZERO = Vector3(0.0f, 0.0f, 0.0f);
const Vector3 Vector3::ONE = Vector3(1.0f, 1.0f, 1.0f);


/*	Static Functions
* * * * * * * * * * * * */
float Vector3::det(const Vector3& a, const Vector3& b)
{
	return (a.x * b.y) - (a.y * b.x) - (a.z * b.z);
}

float Vector3::distance(const Vector3& a, const Vector3& b)
{
	float dx = powf((b.x - a.x), 2);
	float dy = powf((b.y - a.y), 2);
	float dz = powf((b.z - a.z), 2);

	return sqrtf(dx + dy);
}

float Vector3::dot(const Vector3& a, const Vector3& b)
{
	return (a.x * b.x) + (a.y * b.y) + (a.z * b.z);
}


Vector3 Vector3::scale(const Vector3& a, const Vector3& b)
{
	return Vector3(
		(a.x * b.x), 
		(a.y * b.y), 
		(a.z * b.z));
}


/*	Operator Overloads
* * * * * * * * * * * * */
std::ostream& operator<<(std::ostream& out, const Vector3& v)
{
	out 
		<< v.x 
		<< v.y 
		<< v.z;

	return out;
}

std::istream& operator >> (std::istream& in, Vector3& v)
{
	in 
		>> v.x 
		>> v.y 
		>> v.z;

	return in;
}


bool operator!=(const Vector3& lhs, const Vector3& rhs)
{
	return 
		(lhs.x != rhs.x) || 
		(lhs.y != rhs.y) || 
		(lhs.z != rhs.z);
}

bool operator==(const Vector3& lhs, const Vector3& rhs)
{
	return 
		(lhs.x == rhs.x) && 
		(lhs.y == rhs.y) && 
		(lhs.z == rhs.z);
}


Vector3 operator+(const Vector3& lhs, const Vector3& rhs)
{
	return Vector3(
		lhs.x + rhs.x, 
		lhs.y + rhs.y, 
		lhs.z + rhs.z);
}

Vector3& operator+=(Vector3& lhs, const Vector3& rhs)
{
	lhs.x += rhs.x;
	lhs.y += rhs.y;
	lhs.z += rhs.z;

	return lhs;
}


Vector3 operator-(const Vector3& lhs, const Vector3& rhs)
{
	return Vector3(
		lhs.x - rhs.x, 
		lhs.y - rhs.y,
		lhs.z - rhs.z);
}

Vector3& operator-=(Vector3& lhs, const Vector3& rhs)
{
	lhs.x -= rhs.x;
	lhs.y -= rhs.y;
	lhs.z -= rhs.z;

	return lhs;
}


Vector3 operator*(const Vector3& lhs, const float rhs)
{
	return Vector3(
		lhs.x * rhs, 
		lhs.y * rhs,
		lhs.z * rhs);
}

Vector3& operator*=(Vector3& lhs, const float rhs)
{
	lhs.x *= rhs;
	lhs.y *= rhs;
	lhs.z *= rhs;

	return lhs;
}


Vector3 operator/(const Vector3& lhs, const float rhs)
{
	return Vector3(
		lhs.x / rhs, 
		lhs.y / rhs, 
		lhs.z / rhs);
}

Vector3& operator/=(Vector3& lhs, const float rhs)
{
	lhs.x /= rhs;
	lhs.y /= rhs;
	lhs.z /= rhs;

	return lhs;
}