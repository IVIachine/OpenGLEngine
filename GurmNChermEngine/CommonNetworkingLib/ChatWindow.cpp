#include "ChatWindow.h"
#include "EventSystem.h"
#include "ChatEvent.h"
#include "Game.h"
#include "Net.h"

ChatWindow::ChatWindow()
{
}

ChatWindow::~ChatWindow()
{
	cleanup();
}


void ChatWindow::setup()
{
	EVENT_SYSTEM->addListener(EV_CHAT_MESSAGE, this);

	m_font = Font();
	m_font.loadFromFile(Game::ASSET_PATH + "/fonts/minecraft.ttf");

	m_chatBuffer = ChatBuffer(m_font, Color::White);
	m_chatBuffer.setPosition({ 32.f, 32.f });
	m_chatBuffer.setHeight(10);

	m_textField = TextField({ 32.f, GRAPHICS->getHeight() - 48.f }, m_font, Color::White);
	m_textField.setActive(true);
}

void ChatWindow::cleanup()
{
	m_chatBuffer.cleanup();
}

void ChatWindow::update()
{
	mp_user = CLIENT->getUser();

	m_chatBuffer.update();
	m_textField.update();

	if (INPUT->getKeyDown(Keyboard::Keys::Return))
	{
		if (m_textField.size() > 0)
		{
			std::stringstream sstream;
			sstream
				<< "$ " << mp_user->getName() << ": " << m_textField.getString()
				<< "\n";

			ChatMessage chatMessage(sstream.str(), MessageDest::Server);

			EVENT_SYSTEM->fireEvent(ChatEvent(chatMessage));
		}
	}
	if (INPUT->getKeyDown(Keyboard::Keys::Up))
	{
		// scroll up
		m_chatBuffer.modIndex(-1);
	}
	if (INPUT->getKeyDown(Keyboard::Keys::Down))
	{
		// scroll down
		m_chatBuffer.modIndex(1);
	}
	if (INPUT->getKeyDown(Keyboard::Keys::Home))
	{
		// go to begin
		m_chatBuffer.setIndex(m_chatBuffer.begin());
	}
	if (INPUT->getKeyDown(Keyboard::Keys::End))
	{
		// go to end
		m_chatBuffer.setIndex(m_chatBuffer.end());
	}
}

void ChatWindow::draw()
{
	m_chatBuffer.draw();
	
	m_textField.draw();
}

void ChatWindow::handleEvent(const Event& ev)
{
	if (ev.getType() == EV_CHAT_MESSAGE)
	{
		const ChatEvent& chatEvent = static_cast<const ChatEvent&>(ev);

		ChatMessage chatMessage = chatEvent.getMessage();

		if (chatMessage.getDest() == MessageDest::Client)
		{
			m_chatBuffer.print(chatMessage);
		}
	}
}
