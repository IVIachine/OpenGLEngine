#include "Game.h"
#include "EventSystem.h"
#include <stdlib.h>
#include <iostream>   // std::cout
#include <string>     // std::string, std::to_string
//#include "SFML\Window\Event.hpp"

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
	m_camera = new Camera(glm::vec3(0, 0, 0), 70.0f, width / height, 0.01f, 1000.0f);
	GRAPHICS->setup(width, height, "GraphicsTest");

	Transform tmp = Transform(glm::vec3(1.0, 1.0, 1.0), glm::vec3(45, 0, 0));

	m_skybox = new SkyBox("Shaders/basicShader2", "cube.jpg");

	for (int i = 0; i < 20; i++)
	{
		for (int i = 0; i < 5; i++)
		{
			m_Images.push_back(new Image("Shaders/basicShader", "Brick-Texture-1.jpg", "cube.obj", false));
			m_Images.back()->setTransform(tmp);
			tmp.setPos(glm::vec3(tmp.getPos().x + 2, tmp.getPos().y, tmp.getPos().z -10));
		}	
		tmp.setPos(glm::vec3(tmp.getPos().x, tmp.getPos().y, tmp.getPos().z));
		tmp.setPos(glm::vec3(tmp.getPos().x + 2, tmp.getPos().y, tmp.getPos().z));
	}


	m_counter = 0.0f;
	m_isRunning = true;
	loop();
	return true;
}

void Game::cleanup()
{
	Graphics::destroyInstance();

	for (std::vector< Image* >::iterator it = m_Images.begin(); it != m_Images.end(); ++it)
	{
		delete (*it);
	}
	m_Images.clear();
	
	delete m_camera;
	m_camera = NULL;

	delete m_skybox;
	m_skybox = NULL;
}


void Game::loop()
{
	do
	{
		while (GRAPHICS->isWindowOpen() && GRAPHICS->exitWindow())
		{
			GRAPHICS->moveCamera(m_camera);
			update();
			GRAPHICS->clear();
			draw();
			GRAPHICS->pollEvents();
			m_counter += 0.0001f;
		}
		m_isRunning = false;
	} while (m_isRunning);
}

void Game::update()
{
	
}

void Game::draw()
{
	m_skybox->update();
	m_skybox->draw(*m_camera);
	for (size_t i = 0; i < m_Images.size(); i++)
	{
		m_Images[i]->draw(*m_camera);
	}
	GRAPHICS->flip();
}

void Game::handleEvent(const Event& ev)
{

}