#ifndef _EV_CHAT_MESSAGE_H_
#define _EV_CHAT_MESSAGE_H_

#include "Event.h"
#include "ChatMessage.h"

class ChatEvent : public Event
{
public:
	ChatEvent(const ChatMessage& message);
	~ChatEvent();

	ChatMessage getMessage() const;
	void		setMessage(const ChatMessage& message);

private:
	ChatMessage m_message;
};

#endif