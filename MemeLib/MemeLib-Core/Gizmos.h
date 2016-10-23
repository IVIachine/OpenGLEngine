#ifndef _GIZMOS_H_
#define _GIZMOS_H_

#include <glm.hpp>
#include <GL\glew.h>
#include <Trackable.h>
#include <cassert>

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

	bool setup();
	void cleanup();

	void drawRay(glm::vec3 start, glm::vec3 end);

private:
	Gizmos();
	~Gizmos();

	static Gizmos* sp_instance;
};


#endif // !_GIZMOS_G_
