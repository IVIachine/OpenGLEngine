#ifndef _CHAT_COMMAND_H_
#define _CHAT_COMMAND_H_

#include <iostream>
#include "Graphics.h"

enum MessageDest : int
{
	Server = 0,
	Client = 1
};

class ChatMessage
{
public:
	ChatMessage();
	ChatMessage(const std::string& str, MessageDest options);
	ChatMessage(const ChatMessage& copy);
	~ChatMessage();

	std::string	getString() const;
	void		setString(const std::string& str);

	MessageDest	getDest() const;
	void		setDest(MessageDest dest);

	friend std::ostream& operator<<(std::ostream& out, const ChatMessage& cmd);
	friend std::istream& operator>>(std::istream& in, ChatMessage& cmd);

private:
	std::string	m_string;
	MessageDest	m_options;
};

#endif