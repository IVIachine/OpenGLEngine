#include "ChatEvent.h"

ChatEvent::ChatEvent(const ChatMessage& message) 
	: Event(EV_CHAT_MESSAGE)
{
	setMessage(message);
}

ChatEvent::~ChatEvent()
{
}


ChatMessage ChatEvent::getMessage() const
{
	return m_message;
}

void ChatEvent::setMessage(const ChatMessage& message)
{
	m_message = ChatMessage(message);
}