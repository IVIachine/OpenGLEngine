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

	Vertex vertices[] = {
		//Vertices according to faces
		Vertex(glm::vec3(-1.0f, -1.0f, 1.0f), glm::vec2(0.25f, 0.3333f)), //Vertex 0
		Vertex(glm::vec3(1.0f, -1.0f, 1.0f), glm::vec2(0.5f, 0.3333f)),  //v1
		Vertex(glm::vec3(-1.0f, 1.0f, 1.0f), glm::vec2(0.25f, 0.6666f)),  //v2
		Vertex(glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(0.5f, 0.6666f)),   //v3

		Vertex(glm::vec3(1.0f, -1.0f, 1.0f), glm::vec2(0.5f, 0.3333f)),  //...
		Vertex(glm::vec3(1.0f, -1.0f, -1.0f), glm::vec2(0.75f, 0.3333f)), //FIx bot coords here
		Vertex(glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(0.5f, 0.6666f)),
		Vertex(glm::vec3(1.0f, 1.0f, -1.0f), glm::vec2(0.75f, 0.6666f)),

		Vertex(glm::vec3(1.0f, -1.0f, -1.0f), glm::vec2(0.75f, 0.3333f)),
		Vertex(glm::vec3(-1.0f, -1.0f, -1.0f), glm::vec2(1.0f, 0.3333f)),
		Vertex(glm::vec3(1.0f, 1.0f, -1.0f), glm::vec2(0.75f, 0.6666f)),
		Vertex(glm::vec3(-1.0f, 1.0f, -1.0f), glm::vec2(1.0f, 0.6666f)),

		Vertex(glm::vec3(-1.0f, -1.0f, -1.0f), glm::vec2(0.0f, 0.3333f)),
		Vertex(glm::vec3(-1.0f, -1.0f, 1.0f), glm::vec2(0.25f, 0.3333f)),
		Vertex(glm::vec3(-1.0f, 1.0f, -1.0f), glm::vec2(0.0f, 0.6666f)),
		Vertex(glm::vec3(-1.0f, 1.0f, 1.0f), glm::vec2(0.25f, 0.6666f)),

		Vertex(glm::vec3(-1.0f, -1.0f, -1.0f), glm::vec2(0.25f, 0.0f)),
		Vertex(glm::vec3(1.0f, -1.0f, -1.0f), glm::vec2(0.5f, 0.0f)),
		Vertex(glm::vec3(-1.0f, -1.0f, 1.0f), glm::vec2(0.25f, 0.3333f)),
		Vertex(glm::vec3(1.0f, -1.0f, 1.0f), glm::vec2(0.5f, 0.3333f)),

		Vertex(glm::vec3(-1.0f, 1.0f, 1.0f), glm::vec2(0.25f, 0.6666f)),
		Vertex(glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(0.5f, 0.6666f)),
		Vertex(glm::vec3(-1.0f, 1.0f, -1.0f), glm::vec2(0.25f, 1.0f)),
		Vertex(glm::vec3(1.0f, 1.0f, -1.0f), glm::vec2(0.5f, 1.0f))
	};

	unsigned int indices[]{
		//Faces definition
		0,1,3, 0,3,2,           //Face front
		4,5,7, 4,7,6,           //Face right
		8,9,11, 8,11,10,        //... 
		12,13,15, 12,15,14,
		16,17,19, 16,19,18,
		20,21,23, 20,23,22,
	};

	Transform skyBoxTransform = Transform(glm::vec3(0, 0, 0), glm::vec3(0, 0, 0), glm::vec3(500, 500, 500));
	m_skybox = new Image("Shaders/basicShader", vertices, sizeof(vertices) / sizeof(vertices[0]), "box.png", indices, sizeof(indices) / sizeof(indices[0]), true); //CITE: https://reije081.home.xs4all.nl/skyboxes/images/skyboxsun5deg.png
	m_skybox->setTransform(skyBoxTransform);
	tmp.setPos(glm::vec3(tmp.getPos().x + 5, tmp.getPos().y, tmp.getPos().z - 10));
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
	m_skybox->getTransform().setPos(m_camera->getPos());
}

void Game::draw()
{
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