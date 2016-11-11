#ifndef _GIZMOS_H_
#define _GIZMOS_H_

#include "Vector3.h"
#include <GL\glew.h>
#include <Trackable.h>
#include <cassert>
#include "Color.h"
#include "Shader.h"

#define GIZMOS Gizmos::getInstance()

class Gizmos : public Trackable
{
public:
	static Gizmos*	getInstance()
	{
		assert(sp_instance != NULL);
		return sp_instance;
	};
	static Gizmos*	createInstance()
	{
		sp_instance = new Gizmos();
		return getInstance();
	};
	static void		destroyInstance()
	{
		delete sp_instance;
		sp_instance = NULL;
	};

	bool setup(Shader* shader);
	void cleanup();

	void setColor(Color color);

	void drawPoint(Vec2 pos, float d = 0.0f);
	void drawPoint(Vec3 pos);
	void drawRay(Vec3 start, Vec3 end);

private:
	Gizmos();
	~Gizmos();

	static Gizmos* sp_instance;
	Shader* mpShader;
};


#endif // !_GIZMOS_G_
