#ifndef _EVENT_LISTENER_H_
#define _EVENT_LISTENER_H_

#include <Trackable.h>

class Event;

class EventListener : public Trackable
{
public:
	EventListener();
	virtual ~EventListener();

	virtual void handleEvent(const Event& ev) = 0;
};

#endif // !_EVENT_LISTENER_H_
