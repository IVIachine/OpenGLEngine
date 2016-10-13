#ifndef _CHAT_CHANNEL_H_
#define _CHAT_CHANNEL_H_

#include <vector>
#include "ChatMessage.h"

class ChatBuffer
{
public:
	ChatBuffer();
	ChatBuffer(Font font, Color color);
	~ChatBuffer();

	void setup();
	void cleanup();
	void update();
	void draw();

	ChatMessage*getMessage(size_t index);
	void		print(const ChatMessage& message);
	void		clear();

	size_t		getIndex() const;
	bool		setIndex(size_t index);
	void		modIndex(int amount);

	size_t		size() const { return m_buffer.size(); };
	size_t		begin() const { return 0; };
	size_t		end() const { return size() - m_height; };

	size_t		getHeight() const { return m_height; }
	Vector2		getPosition() const { return m_position; }

	void		setHeight(size_t value) { m_height = value; }
	void		setPosition(Vector2 value) { m_position = value; }

private:
	Vector2	m_position;
	Text	m_text;
	Font	m_font;
	Color	m_color;

	std::vector<ChatMessage> m_buffer;
	size_t	m_height;
	size_t	m_index;
};

#endif // !_CHAT_CHANNEL_H_
