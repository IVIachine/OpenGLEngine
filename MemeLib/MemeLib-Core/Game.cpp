#include "Game.h"
#include "EventSystem.h"
#include "GameMessageManager.h"
#include "Input.h"
#include "Gizmos.h"

Game* Game::sp_instance = NULL;

Game::Game()
{

}

Game::~Game()
{
	cleanup();
}


bool Game::setup(int width, int height)
{
	// Setup Timers
	mp_loopTimer = new Timer;
	mp_masterTimer = new Timer;

	// Setup ResourceManager
	if (!ResourceManager::createInstance()->setup())
	{
		fprintf(stderr, "Failed to initialize Time.\n");
		return false;
	}

	// Setup Time
	if (!Time::createInstance()->setup())
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

	m_isRunning = true;
	return m_isRunning;
}

void Game::cleanup()
{
	// Dispose timers
	delete mp_loopTimer;
	mp_loopTimer = NULL;

	delete mp_masterTimer;
	mp_masterTimer = NULL;

	// Dispose ResourceManager
	ResourceManager::destroyInstance();

	// Dispose Time
	Time::destroyInstance();

	// Dispose Graphics
	Graphics::destroyInstance();

	// Dispose Gizmos
	Gizmos::destroyInstance();

	// Dispost Input
	Input::destroyInstance();

	// Dispose GameMessageManager
	GameMessageManager::destroyInstance();
}


void Game::beginStep()
{
	INPUT->beginStep();
	TIME->beginStep();

	mp_loopTimer->start();
}

void Game::step()
{
	TIME->step();

	MESSAGES->processMessagesForThisframe();

	if (INPUT->getKeyDown(Keyboard::KeyCode::Escape))
	{
		m_stopRequested = true;
	}

	// Exit application if stop requested
	if (m_stopRequested)
	{
		m_isRunning = false;
	}
}

bool Game::endStep()
{
	GRAPHICS->pollEvents();
	INPUT->endStep();
	TIME->endStep();

	mp_loopTimer->sleepUntilElapsed(m_fps);

	return m_isRunning;
}

void Game::handleEvent(const Event& ev)
{

}