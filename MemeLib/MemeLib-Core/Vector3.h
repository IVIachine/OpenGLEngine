#ifndef _VECTOR3_H_
#define _VECTOR3_H_

#include <glm.hpp>
#include <Trackable.h>

class Vector3 : public Trackable
{
public:
	/*	Constructors
	* * * * * * * * * * * * */
	Vector3();
	Vector3(float x, float y, float z);
	Vector3(const Vector3 &copy);
	~Vector3();

	/*	Variables
	* * * * * * * * * * * * */
	float x;
	float y;
	float z;

	/*	Functions
	* * * * * * * * * * * * */
	float	getX() const;
	float	getY() const;
	float	getZ() const;

	void	setX(float value);
	void	setY(float value);
	void	setZ(float value);

	float	magnitude();
	float	sqaredMagnitude();

	void	normalize();
	Vector3 normalized();



	glm::vec3 vec3() const
	{
		return{ x, y, z };
	};

	Vector3(const glm::vec3& vec3)
	{
		x = vec3.x;
		y = vec3.y;
		z = vec3.z;
	};



	/*	Constants
	* * * * * * * * * * * * */
	static const Vector3 ZERO;
	static const Vector3 ONE;


	/*	Static Functions
	* * * * * * * * * * * * */
	static float	det(const Vector3& a, const Vector3& b);
	static float	distance(const Vector3& a, const Vector3& b);
	static float	dot(const Vector3& a, const Vector3& b);

	static Vector3	scale(const Vector3& a, const Vector3& b);


	/*	Operator Overloads
	* * * * * * * * * * * * */
	friend std::ostream& operator<<(std::ostream& out, const Vector3& v);
	friend std::istream& operator>>(std::istream& in, Vector3& v);


	friend bool operator!=(const Vector3& lhs, const Vector3& rhs);
	friend bool operator==(const Vector3& lhs, const Vector3& rhs);


	friend Vector3 operator+(const Vector3& lhs, const Vector3& rhs);
	friend Vector3& operator+=(Vector3& lhs, const Vector3& rhs);


	friend Vector3 operator-(const Vector3& lhs, const Vector3& rhs);
	friend Vector3& operator-=(Vector3& lhs, const Vector3& rhs);


	friend Vector3 operator*(const Vector3& lhs, const float rhs);
	friend Vector3& operator*=(Vector3& lhs, const float rhs);


	friend Vector3 operator/(const Vector3& lhs, const float rhs);
	friend Vector3& operator/=(Vector3& lhs, const float rhs);
};

#endif // !_VECTOR3_H_
