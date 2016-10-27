#ifndef _GIZMOS_H_
#define _GIZMOS_H_

#include <glm.hpp>
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

	void drawPoint(glm::vec3 pos, Camera camera, Transform transform);
	void drawRay(glm::vec3 start, glm::vec3 end, Camera camera, Transform transform);

private:
	Gizmos();
	~Gizmos();

	static Gizmos* sp_instance;
	Shader* mpShader;
};


#endif // !_GIZMOS_G_
