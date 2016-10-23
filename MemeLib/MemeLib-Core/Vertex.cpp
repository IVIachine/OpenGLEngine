#include "Vertex.h"

Vertex::Vertex(const glm::vec3 & pos, const glm::vec2 coord)
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

glm::vec3 * Vertex::getPos()
{
	return &m_pos;
}

glm::vec2 * Vertex::getCoord()
{
	return &m_textCoord;
}
