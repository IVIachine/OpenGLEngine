#include "ChatMessage.h"

ChatMessage::ChatMessage()
{
	m_string = "";
	m_options = MessageDest::Server;
}

ChatMessage::ChatMessage(const std::string& str, MessageDest options)
{
	m_string = str;
	m_options = options;
}

ChatMessage::ChatMessage(const ChatMessage& copy)
{
	m_string = copy.m_string;
	m_options = copy.m_options;
}

ChatMessage::~ChatMessage()
{
}


std::string ChatMessage::getString() const
{
	return m_string;
}

void ChatMessage::setString(const std::string& str)
{
	m_string = str;
}


MessageDest ChatMessage::getDest() const
{
	return m_options;
}

void ChatMessage::setDest(MessageDest dest)
{
	m_options = dest;
}


std::ostream& operator<<(std::ostream& out, const ChatMessage& message)
{
	out << message.m_string;

	return out;
}

std::istream& operator>>(std::istream& in, ChatMessage& message)
{
	in >> message.m_string;

	return in;
}