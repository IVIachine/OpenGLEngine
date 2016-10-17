#include "Event.h"

Event::Event(EventType type) : m_type(type)
{
}

Event::~Event()
{
}


const std::string& Event::getName() const
{
	if (m_type > INVALID_EVENT_TYPE && m_type < NUM_EVENT_TYPES)
	{
		return EVENT_NAMES[m_type];
	}
	else
	{
		static const std::string nullString;

		return nullString;
	}
}

EventType Event::getType() const
{
	return m_type;
}