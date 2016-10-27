#include "Gizmos.h"
#include "Graphics.h"

Gizmos* Gizmos::sp_instance = NULL;


Gizmos::Gizmos()
{
}

Gizmos::~Gizmos()
{
}


bool Gizmos::setup(Shader* shader)
{
	mpShader = shader;
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


void Gizmos::drawPoint(Vec3 pos)
{
	float
		x1 = pos.x,
		y1 = pos.y,
		z1 = pos.z;
	Camera* camera = GRAPHICS->getCamera();
	Transform transform = Transform(pos, Vec3(0, 0, 0), Vec3(0, 0, 0));
	mpShader->bind();
	mpShader->update(transform, *camera);
	

	glDisable(GL_TEXTURE_2D);
	glDisable(GL_LIGHTING);
	glEnable(GL_COLOR_MATERIAL);
	glColorMaterial(GL_FRONT_AND_BACK, GL_DIFFUSE);
	glColor3f(0.0f, 0.0f, 1.0f); //blue color

	glPointSize(10.0f);

	glBegin(GL_POINTS);	
	glVertex3f(x1, y1, z1);
	glEnd();
}

void Gizmos::drawRay(Vec3 start, Vec3 end)
{
	Camera* camera = GRAPHICS->getCamera();
	float
		x1 = start.x,
		y1 = start.y,
		z1 = start.z;

	float
		x2 = end.x,
		y2 = end.y,
		z2 = end.z;

	Transform transform = Transform(Vec3((start.x - end.x) / camera->getFOV(), (start.y - end.y) / camera->getFOV(), (start.z - end.z) / camera->getFOV()), Vec3(0, 0, 0), Vec3(1, 1, 1));
	mpShader->bind();
	mpShader->update(transform, *camera);

	glBegin(GL_LINES);
	glVertex3f(x1, y1, z1);
	glVertex3f(x2, y2, z2);
	glEnd();
}
