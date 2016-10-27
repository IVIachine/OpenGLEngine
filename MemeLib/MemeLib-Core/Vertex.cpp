#include "Vertex.h"

Vertex::Vertex(const Vec3 & pos, const Vec2 coord)
{
	m_pos = pos;
	m_textCoord = coord;
}

Vertex::Vertex(const Vertex & copy)
{
	m_pos = copy.m_pos;
	m_textCoord = copy.m_textCoord;
}

Vertex::Vertex()
{
}

Vec3 * Vertex::getPos()
{
	return &m_pos;
}

Vec2 * Vertex::getCoord()
{
	return &m_textCoord;
}
