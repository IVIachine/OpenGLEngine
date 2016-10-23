#include "Gizmos.h"

Gizmos* Gizmos::sp_instance = NULL;


Gizmos::Gizmos()
{
}

Gizmos::~Gizmos()
{
}


bool Gizmos::setup()
{
	return true;
}

void Gizmos::cleanup()
{
}


void Gizmos::drawPoint(glm::vec3 pos)
{
	glBegin(GL_POINT);
	glVertex3f(pos.x, pos.y, pos.z);
	glEnd();
}

void Gizmos::drawRay(glm::vec3 start, glm::vec3 end)
{
	float 
		x1 = start.x, 
		y1 = start.y,
		z1 = start.z;

	float 
		x2 = end.x,
		y2 = end.y,
		z2 = end.z;
	
	glBegin(GL_LINES);
	glVertex3f(x1, y1, z1);
	glVertex3f(x2, y2, z2);
	glEnd();
}
