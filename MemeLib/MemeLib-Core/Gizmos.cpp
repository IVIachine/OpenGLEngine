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

void Gizmos::setColor(Color color)
{
	glColor4ui(
		color.r, 
		color.g, 
		color.b, 
		color.a);
}


void Gizmos::drawPoint(glm::vec3 pos)
{
	float
		x1 = pos.x,
		y1 = pos.y,
		z1 = pos.z;

	glColor3f(0.0f, 0.0f, 1.0f); //blue color

	glPointSize(10.0f);

	glBegin(GL_POINTS);	
	glVertex3f(x1, y1, z1);
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
