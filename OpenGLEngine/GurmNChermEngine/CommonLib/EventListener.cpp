#include "EventListener.h"
#include "EventSystem.h"

EventListener::EventListener()
{
}

EventListener::~EventListener()
{
	if (EVENT_SYSTEM != NULL)
	{
		EVENT_SYSTEM->removeListenerFromAllEvents(this);
	}
}