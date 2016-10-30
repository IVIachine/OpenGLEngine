#ifndef _EVENT_H_
#define _EVENT_H_

#include <iostream>
#include <Trackable.h>

enum EventType
{
	INVALID_EVENT_TYPE = -1,
	EV_CHAT_MESSAGE,
	SPAWN_EVENT,
	PATH_EVENT,
	TARGET_EVENT,
	NUM_EVENT_TYPES
};

const std::string EVENT_NAMES[NUM_EVENT_TYPES] = { "Event" };

class Event : public Trackable
{
public:
	Event(EventType type);
	virtual ~Event();

	const std::string&	getName() const;
	EventType			getType() const;

private:
	EventType m_type;
};

#endif