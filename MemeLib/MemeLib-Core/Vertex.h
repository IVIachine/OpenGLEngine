#ifndef _VERTEX_H_
#define _VERTEX_H_

#include "Vector3.h"
#include "Vector2.h"
#include <GL\glew.h>
#include <Trackable.h>

class Vertex : public Trackable
{
public:
	Vertex();
	Vertex(const Vec3& pos, const Vec2 coord);
	Vertex(const Vertex& copy);

	Vec3* getPos();
	Vec2* getCoord();

private:
	Vec3 m_pos;
	Vec2 m_textCoord;
};

#endif // !_VERTEX_H_
