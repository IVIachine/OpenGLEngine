#include "EventSystem.h"
#include "Event.h"
#include "EventListener.h"

EventSystem* EventSystem::sp_instance = NULL;

EventSystem::EventSystem()
{
}

EventSystem::~EventSystem()
{
}


EventSystem* EventSystem::getInstance()
{
	assert(sp_instance != NULL);
	return sp_instance;
}

void EventSystem::destroyInstance()
{
	delete sp_instance;
	sp_instance = NULL;
}

EventSystem* EventSystem::createInstance()
{
	sp_instance = new EventSystem();
	return getInstance();
}


void EventSystem::addListener(EventType type, EventListener* listener)
{
	m_eventListenerMap.insert(std::pair< EventType, EventListener*>(type, listener));
}

void EventSystem::removeListener(EventType type, EventListener* listener)
{
	std::pair<
		std::multimap<EventType, EventListener*>::iterator, 
		std::multimap<EventType, EventListener*>::iterator> ret;

	ret = m_eventListenerMap.equal_range(type);
	std::multimap<EventType, EventListener*>::iterator iter;

	for (iter = ret.first; iter != ret.second; ++iter)
	{
		if (iter->second == listener)
		{
			m_eventListenerMap.erase(iter);

			break; // to prevent using invalidated iterator
		}
	}
}

void EventSystem::removeListenerFromAllEvents(EventListener* listener)
{
	std::multimap<EventType, EventListener*>::iterator iter;

	bool allTheWayThrough = false;

	while (!allTheWayThrough)
	{
		allTheWayThrough = true;

		for (iter = m_eventListenerMap.begin(); iter != m_eventListenerMap.end(); ++iter)
		{
			if (iter->second == listener)
			{
				m_eventListenerMap.erase(iter);
				
				allTheWayThrough = false; // didn't make it the whole way through

				break; // to prevent using invalidated iterator
			}
		}
	}
}

void EventSystem::fireEvent(const Event& ev)
{
	dispatchAllEvents(ev);
}

void EventSystem::dispatchAllEvents(const Event& ev)
{
	std::pair<std::multimap<EventType, EventListener*>::iterator, std::multimap<EventType, EventListener*>::iterator> ret;
	ret = m_eventListenerMap.equal_range(ev.getType());

	std::multimap<EventType, EventListener*>::iterator iter;
	for (iter = ret.first; iter != ret.second; ++iter)
	{
		iter->second->handleEvent(ev);
	}

}