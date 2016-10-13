#ifndef _CAMERA_H_
#define _CAMERA_H_


#include <SFML/Graphics.hpp>
#include "Rect.h"

class Graphics;

class Camera
{
public:
	Camera();
	Camera(const Vector2& center, const Vector2& size);
	~Camera();

	friend class Graphics;

	Vector2		getCenter();
	void		setCenter(const Vector2& center);
	
	Vector2		getSize();
	void		setSize(const Vector2& size);
	
	float		getRotation();
	void		setRotation(float angle);
	
	Rect		getViewport();
	void		setViewport(const Rect& viewport);

	void		reset(Rect rect);

	void		move(Vector2 offset);
	void		rotate(float angle);
	void		zoom(float factor);


private:
	sf::View mView_sf;

	float
		mZoom,
		mRotation;

	Vector2
		mSize,
		mCenter;

	Rect mViewport;
};

#endif