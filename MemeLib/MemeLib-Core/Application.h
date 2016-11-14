#ifndef _APPLICATION_H_
#define _APPLICATION_H_

#include "EventListener.h"

class Application : public EventListener
{
public:
	Application();
	virtual ~Application();

	virtual bool setup() = 0;
	virtual void clear() = 0;
	virtual void update() = 0;
	virtual void draw() = 0;
	virtual void handleEvent(const Event& ev) = 0;

private:

};

#endif // !_APPLICATION_H_
