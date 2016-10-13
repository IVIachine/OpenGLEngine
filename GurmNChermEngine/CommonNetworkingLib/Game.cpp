#include "Game.h"
#include "EventSystem.h"
#include <stdlib.h>
#include <iostream>   // std::cout
#include <string>     // std::string, std::to_string
#include "SFML\Window\Event.hpp"

Game* Game::sp_instance = NULL;
const std::string Game::ASSET_PATH = "../Assets";

Game::Game()
{
	
}

Game::~Game()
{
	cleanup();
}


Game* Game::getInstance()
{
	assert(sp_instance != NULL);
	return sp_instance;
}

void Game::destroyInstance()
{
	delete sp_instance;
	sp_instance = NULL;
}

Game* Game::createInstance()
{
	sp_instance = new Game();
	return getInstance();
}


bool Game::setup(int width, int height)
{
	Graphics::createInstance();
	Texture2DManager::createInstance();
	UnitManager::createInstance();
	GameController::createInstance();
	NetClient::createInstance();
	Input::createInstance();


	m_addressString = "";
	std::cout << "Enter server IP or hit enter for " << LOCAL_HOST << "\n";
	std::getline(std::cin, m_addressString);
	if (m_addressString[0] == 0) 
	{
		m_addressString = LOCAL_HOST;
	}

	GRAPHICS->setup(width, height, "SFML Window");

	m_chat = ChatWindow();
	m_chat.setup();

	m_font = Font();
	m_font.loadFromFile(Game::ASSET_PATH + "/fonts/minecraft.ttf");
	m_loginField = TextField(Vector2(50, 50), m_font, Color::White);
	m_loginField.setActive(true);
	m_isRunning = true;
	//m_isLogin = true;
	loop();

	return true;
}

void Game::cleanup()
{
	m_chat.cleanup();

	Graphics::destroyInstance();
	Texture2DManager::destroyInstance();
	UnitManager::destroyInstance();
	GameController::destroyInstance();
	NetClient::destroyInstance();
	Input::destroyInstance();
}


void Game::loop()
{
	do
	{
		while (GRAPHICS->isWindowOpen())
		{
			INPUT->beginStep();
			{
				update();

				GRAPHICS->clear();
				{
					draw();
				}
				GRAPHICS->pollEvents();
			}
			INPUT->endStep();
		}
	} 
	while (m_isRunning);
}

void Game::update()
{
	if (m_loginField.isActive())
	{
		std::string name = m_loginField.peekString();

		if (INPUT->getKeyDown(Keyboard::Keys::Return) && name != "")
		{
			CLIENT->setAddress(m_addressString);
			CLIENT->setup();
			CLIENT->setUser(User(
				m_loginField.getString(),
				m_addressString));

			m_loginField.clear();
			m_loginField.setActive(false);
		}
	}
	else
	{
		CLIENT->update();
	}

	m_loginField.update();
	m_chat.update();

	UNIT_MANAGER->update();
}

void Game::draw()
{
	UNIT_MANAGER->draw();
	
	m_loginField.draw();
	
	m_chat.draw();
}

void Game::handleEvent(const Event& ev)
{
	
}