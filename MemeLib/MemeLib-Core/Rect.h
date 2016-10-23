#ifndef _RECT_H_
#define _RECT_H_

#include <iostream>
#include <Trackable.h>

class Vector2;

class Rect : public Trackable
{
public:
	/*	Constructors
	* * * * * * * * * * * * */
	Rect();
	Rect(float x, float y, float width, float height);
	Rect(Vector2 position, Vector2 size);
	Rect(const Rect& copy);
	~Rect();

	/*	Variables
	* * * * * * * * * * * * */
	float x;
	float y;
	float width;
	float height;


	/*	Static Functions
	* * * * * * * * * * * * */
	static Rect minMaxRect(Vector2 min, Vector2 max);


	/*	Functions
	* * * * * * * * * * * * */
	float getX() const { return x; }
	float getY() const { return y; }
	void setX(float value) { x = value; }
	void setY(float value) { y = value; }

	Vector2 getCenter() const;
	Vector2 getMax() const;
	Vector2 getMin() const;
	Vector2 getPosition() const;
	Vector2 getSize() const;

	float getXMax() const;
	float getYMax() const;
	float getXMin() const;
	float getYMin() const;

	void setCenter(Vector2 pos);
	void setMax(Vector2 pos);
	void setMin(Vector2 pos);
	void setPosition(Vector2 pos);
	void setSize(Vector2 size);

	void setXMax(float value);
	void setYMax(float value);
	void setXMin(float value);
	void setYMin(float value);

	bool contains(Vector2 pos);
	bool overlaps(Rect rect);


	/*	Operator Overloads
	* * * * * * * * * * * * */
	friend std::ostream& operator<<(std::ostream& out, const Rect& r);
	friend std::istream& operator >> (std::istream& in, Rect& r);

	friend bool operator!=(const Rect& lhs, const Rect& rhs);
	friend bool operator==(const Rect& lhs, const Rect& rhs);
};

#endif // !_RECTANGLE_H_
