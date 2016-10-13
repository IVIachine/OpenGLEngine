#ifndef _RECTANGLE_SHAPE_H_
#define _RECTANGLE_SHAPE_H_

#include "Texture2D.h"
#include "Color.h"
#include "Rect.h"

class Graphics;

class RectShape
{
public:
	RectShape();
	RectShape(Rect rect);
	RectShape(const RectShape& copy);
	~RectShape();

	friend class Graphics;

	void		setFillColor(Color color);
	void		setOutlineColor(Color color);
	void		setOutlineThickness(float thickness);

	Color		getFillColor();
	Color		getOutlineColor();
	float		getOutlineThickness();

	void		setPosition(Vector2 position);
	void		setScale(Vector2 scale);
	void		setOrigin(Vector2 origin);
	void		setRotation(float angle);
	void		setSize(Vector2 size);
	void		setBounds(Rect bounds);

	Vector2		getPosition();
	Vector2		getScale();
	Vector2		getOrigin();
	float		getRotation();
	Vector2		getSize();
	Rect		getBounds();

private:
	sf::RectangleShape m_sf_rectangleShape;
	Rect	m_bounds;
	Color	m_fillColor;
	Color	m_outlineColor;
	Vector2 m_scale;
	Vector2 m_origin;
	float	m_rotation;
	float	m_outlineThickness;
};

#endif