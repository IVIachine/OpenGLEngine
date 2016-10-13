#include "RectShape.h"

RectShape::RectShape()
{
	m_bounds = Rect();
	m_sf_rectangleShape = sf::RectangleShape();

	setPosition(m_bounds.position());
	setSize(m_bounds.size());
	setFillColor(Color::Clear);
	setOutlineColor(Color::Clear);
	setOutlineThickness(1);
}

RectShape::RectShape(Rect rect)
{
	m_bounds = rect;
	m_sf_rectangleShape = sf::RectangleShape();

	setPosition(m_bounds.position());
	setSize(m_bounds.size());
	setFillColor(Color::Clear);
	setOutlineColor(Color::Clear);
	setOutlineThickness(1);
}

RectShape::RectShape(const RectShape& copy)
{
	m_sf_rectangleShape = copy.m_sf_rectangleShape;

	m_bounds = copy.m_bounds;
	m_fillColor = copy.m_fillColor;
	m_outlineColor = copy.m_outlineColor;
	m_scale = copy.m_scale;
	m_origin = copy.m_origin;
	m_rotation = copy.m_rotation;
	m_outlineThickness = copy.m_outlineThickness;
}

RectShape::~RectShape()
{

}


void RectShape::setFillColor(Color color)
{
	m_fillColor = color;
	m_sf_rectangleShape.setFillColor(
	{
		m_fillColor.r,
		m_fillColor.g,
		m_fillColor.b,
		m_fillColor.a
	});
}

void RectShape::setOutlineColor(Color color)
{
	m_outlineColor = color;
	m_sf_rectangleShape.setOutlineColor(
	{
		m_outlineColor.r,
		m_outlineColor.g,
		m_outlineColor.b,
		m_outlineColor.a
	});
}

void RectShape::setOutlineThickness(float thickness)
{
	m_outlineThickness = thickness;
	m_sf_rectangleShape.setOutlineThickness(m_outlineThickness);
}


Color RectShape::getFillColor()
{
	return m_fillColor;
}

Color RectShape::getOutlineColor()
{
	return m_outlineColor;
}

float RectShape::getOutlineThickness()
{
	return m_outlineThickness;
}


void RectShape::setPosition(Vector2 position)
{
	m_bounds.position() = position;

	m_sf_rectangleShape.setPosition(
	{
		m_bounds.position().x,
		m_bounds.position().y
	});
}

void RectShape::setScale(Vector2 scale)
{
	m_scale = scale;

	m_sf_rectangleShape.setScale(
	{
		m_scale.x,
		m_scale.y
	});
}

void RectShape::setOrigin(Vector2 origin)
{
	m_origin = origin;

	m_sf_rectangleShape.setOrigin(
	{
		m_origin.x,
		m_origin.y
	});
}

void RectShape::setRotation(float angle)
{
	m_rotation = angle;

	m_sf_rectangleShape.setRotation(m_rotation);
}

void RectShape::setSize(Vector2 size)
{
	m_bounds.size() = size;

	m_sf_rectangleShape.setSize(
	{
		m_bounds.size().x,
		m_bounds.size().y
	});
}

void RectShape::setBounds(Rect bounds)
{
	setPosition(bounds.position());
	setSize(bounds.size());
}


Vector2 RectShape::getPosition()
{
	return m_bounds.position();
}

Vector2 RectShape::getScale()
{
	return m_scale;
}

Vector2 RectShape::getOrigin()
{
	return m_origin;
}

float RectShape::getRotation()
{
	return m_rotation;
}

Vector2 RectShape::getSize()
{
	return m_bounds.size();
}

Rect RectShape::getBounds()
{
	Rect bounds(
		m_bounds.position() - m_origin,
		m_bounds.size());

	return bounds;
}