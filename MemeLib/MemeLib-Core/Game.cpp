#include "Game.h"
#include "EventSystem.h"
#include "GameMessageManager.h"
#include "Input.h"
#include "Gizmos.h"
#include "Application.h"
#include "GameObjectManager.h"

Game* Game::sp_instance = NULL;

Game::Game()
{

}

Game::~Game()
{
	clear();
}


bool Game::setup(int width, int height, Application* pApp)
{
	// Setup ResourceManager
	if (!ResourceManager::createInstance()->setup())
	{
		fprintf(stderr, "Failed to initialize Time.\n");
		return false;
	}

	// Setup Time
	if (!GameTime::createInstance()->setup())
	{
		fprintf(stderr, "Failed to initialize Time.\n");
		return false;
	}

	// Setup Graphics
	if (!Graphics::createInstance()->setup(width, height, "GraphicsTest"))
	{
		fprintf(stderr, "Failed to initialize Graphics.\n");
		return false;
	}

	// Setup Gizmos
	Shader* p_shader3 = RESOURCES->addShader("gizmos", "../Assets/shaders/basicShader3");
	if (!Gizmos::createInstance()->setup(p_shader3))
	{
		fprintf(stderr, "Failed to initialize Gizmos.\n");
		return false;
	}

	// Setup Input
	if (!Input::createInstance()->setup())
	{
		fprintf(stderr, "Failed to initialize Input.\n");
		return false;
	}

	// Setup GameMessageManager
	if (!GameMessageManager::createInstance()->setup())
	{
		fprintf(stderr, "Failed to initialize GameMessageManager.\n");
		return false;
	}

	// Setup GameMessageManager
	if (!GameObjectManager::createInstance()->setup())
	{
		fprintf(stderr, "Failed to initialize GameObjectManager.\n");
		return false;
	}

	// Setup Application
	mp_app = pApp;
	if (!mp_app || !mp_app->setup())
	{
		fprintf(stderr, "Failed to initialize Application.\n");
		return false;
	}

	m_isRunning = true;
	return m_isRunning;
}

void Game::clear()
{
	mp_app->clear();

	// Dispose ResourceManager
	ResourceManager::destroyInstance();

	// Dispose Time
	GameTime::destroyInstance();

	// Dispose Graphics
	Graphics::destroyInstance();

	// Dispose Gizmos
	Gizmos::destroyInstance();

	// Dispost Input
	Input::destroyInstance();

	// Dispose GameMessageManager
	GameMessageManager::destroyInstance();

	// Dispose GameObjectManager
	GameObjectManager::destroyInstance();
}


void Game::beginStep()
{
	INPUT->beginStep();
	TIME->beginStep();
}

void Game::step()
{
	TIME->step();

	MESSAGES->processMessagesForThisframe();

	mp_app->update();
	OBJECT_MANAGER->update();

	GRAPHICS->clear();
	{
		mp_app->draw();
		OBJECT_MANAGER->draw();
	}
	GRAPHICS->flip();
}

bool Game::endStep()
{
	GRAPHICS->pollEvents();
	INPUT->endStep();
	TIME->endStep();

	// Exit application if stop requested
	if (m_stopRequested)
	{
		m_isRunning = false;
	}

	return m_isRunning;
}

void Game::handleEvent(const Event& ev)
{

}