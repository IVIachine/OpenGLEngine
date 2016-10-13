#include "Camera.h"

Camera::Camera()
{

}

Camera::Camera(const Vector2& center, const Vector2& size)
{
	
}

Camera::~Camera()
{

}


Vector2	Camera::getCenter()
{
	return mCenter;
}

void Camera::setCenter(const Vector2& center)
{
	mCenter = center;
	mView_sf.setCenter(mCenter.x, mCenter.y);
}


Vector2	Camera::getSize()
{
	return mSize;
}

void Camera::setSize(const Vector2& size)
{
	mSize = size;
	mView_sf.setSize(mSize.x, mSize.y);
}


float Camera::getRotation()
{
	return mRotation;
}

void Camera::setRotation(float angle)
{
	mRotation = angle;
	mView_sf.setRotation(mRotation);
}


Rect Camera::getViewport()
{
	return mViewport;
}

void Camera::setViewport(const Rect& viewport)
{
	mViewport = viewport;

	sf::FloatRect fr(
		mViewport.position().x,
		mViewport.position().y, 
		mViewport.size().x, 
		mViewport.size().y);

	mView_sf.setViewport(fr);
}


void Camera::reset(Rect rect)
{
	sf::FloatRect fr(
		rect.position().x,
		rect.position().y,
		rect.size().x,
		rect.size().y);

	mView_sf.reset(fr);
}


void Camera::move(Vector2 offset)
{
	mView_sf.move(offset.x, offset.y);
	mCenter = Vector2(mView_sf.getCenter().x, mView_sf.getCenter().y);
}

void Camera::rotate(float angle)
{
	mView_sf.rotate(angle);
	mRotation = mView_sf.getRotation();
}

void Camera::zoom(float factor)
{
	mView_sf.zoom(factor);
}