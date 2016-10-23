#ifndef _VERTEX_H_
#define _VERTEX_H_

#include <glm.hpp>
#include <GL\glew.h>
#include <Trackable.h>

class Vertex : public Trackable
{
public:
	Vertex();
	Vertex(const glm::vec3& pos, const glm::vec2 coord);
	Vertex(const Vertex& copy);

	glm::vec3* getPos();
	glm::vec2* getCoord();

private:
	glm::vec3 m_pos;
	glm::vec2 m_textCoord;
};

#endif // !_VERTEX_H_
