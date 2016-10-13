#include "ChatBuffer.h"

ChatBuffer::ChatBuffer()
{
	setup();
}

ChatBuffer::ChatBuffer(Font font, Color color)
{
	setup();

	m_font = font;
	m_color = color;
}

ChatBuffer::~ChatBuffer()
{
}


void ChatBuffer::setup()
{
	m_font = Font();
	m_color = Color::White;

	m_buffer = std::vector<ChatMessage>();
	m_position = Vector2::ZERO;

	m_text = Text();

	m_height = 10;
	m_index = 0;
}

void ChatBuffer::cleanup()
{

}

void ChatBuffer::update()
{
	std::string str = "";

	size_t begin = m_index;
	size_t end = m_index + m_height;

	for (size_t i = begin; i < end; i++)
	{
		if (i < size())
		{
			str += getMessage(i)->getString();
		}
	}

	m_text.setFont(&m_font);
	m_text.setString(str);
	m_text.setPosition(m_position);
	m_text.setFillColor(m_color);
}

void ChatBuffer::draw()
{
	GRAPHICS->draw(m_text);
}


ChatMessage* ChatBuffer::getMessage(size_t index)
{
	if (index < m_buffer.size())
	{
		return &m_buffer[index];
	}

	return NULL;
}

void ChatBuffer::print(const ChatMessage& message)
{
	m_buffer.push_back(ChatMessage(message));

	if (size() >= m_height)
	{
		setIndex(end());
	}
}

void ChatBuffer::clear()
{
	m_buffer.clear();
}


size_t ChatBuffer::getIndex() const
{
	return m_index;
}

bool ChatBuffer::setIndex(size_t index)
{
	if (index >= 0 && index < size())
	{
		m_index = index;

		return true;
	}

	return false;
}

void ChatBuffer::modIndex(int amount)
{
	size_t index = (m_index + amount);

	if (index >= 0 && index + m_height <= size())
	{
		setIndex(index);
	}

	std::cout << m_index << std::endl;
}