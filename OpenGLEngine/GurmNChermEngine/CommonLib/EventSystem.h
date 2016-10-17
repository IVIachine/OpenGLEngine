#ifndef _EVENT_SYSTEM_H_
#define _EVENT_SYSTEM_H_

#include <cassert>
#include <map>

class Event;
class EventListener;
enum EventType;

#define EVENT_SYSTEM EventSystem::getInstance()

class EventSystem
{
public:
	static EventSystem*	getInstance();
	static EventSystem*	createInstance();
	static void			destroyInstance();

	void fireEvent(const Event& ev);
	void addListener(EventType type, EventListener* listener);
	void removeListener(EventType type, EventListener* listener);
	void removeListenerFromAllEvents(EventListener* listener);

private:
	EventSystem();
	~EventSystem();

	std::multimap< EventType, EventListener* > m_eventListenerMap;

	void dispatchAllEvents(const Event& ev);

	static EventSystem* sp_instance;
};

#endif // !_EVENT_SYSTEM_H_
