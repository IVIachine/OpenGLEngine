#ifndef _CHAT_WINDOW_H_
#define _CHAT_WINDOW_H_

#include <sstream>

#include "ChatBuffer.h"
#include "Event.h"
#include "EventListener.h"
#include "TextField.h"
#include "UserDatabase.h"

class ChatWindow : public EventListener
{
public:
	ChatWindow();
	~ChatWindow();	

	void setup();
	void cleanup();
	void update();
	void draw();	
	virtual void handleEvent(const Event& ev);

private:
	std::string		m_name;
	User*			mp_user;

	Font		m_font;
	ChatBuffer	m_chatBuffer;
	TextField	m_textField;
	
};

#endif // !_CHAT_WINDOW_H_
