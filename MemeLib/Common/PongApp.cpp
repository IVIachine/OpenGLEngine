#include "PongApp.h"
#include <Input.h>
#include <Gizmos.h>
#include <EventSystem.h>
#include <GameObjectManager.h>
#include <ResourceManager.h>
#include "NetServer.h"
#include "NetClient.h"

PongApp::PongApp()
{
}

PongApp::~PongApp()
{
}


bool PongApp::setup()
{
	// Setup Graphics
	GRAPHICS->getCamera()->setPosition({ 0, 0, -10 });
	GRAPHICS->getCamera()->setForward({ 0, 0, 1 });
	GRAPHICS->enableMouseLook(false);

	// Load Resources
	Shader* p_shader = RESOURCES->addShader("basic", "../Assets/shaders/basicShader");

	RESOURCES->addTexture("paddle1", "../Assets/textures/Pong/paddleBlue.png");
	RESOURCES->addTexture("ball", "../Assets/textures/Pong/ball.png");

	RESOURCES->addTexture2D("paddle1", RESOURCES->getTexture("paddle1"), p_shader);
	RESOURCES->addTexture2D("ball", RESOURCES->getTexture("ball"), p_shader);

	RESOURCES->addSprite("paddle1", RESOURCES->getTexture2D("paddle1"));
	RESOURCES->addSprite("ball", RESOURCES->getTexture2D("ball"));
	return true;
}

void PongApp::clear()
{
}

void PongApp::update()
{
	if (INPUT->getKeyDown(Keyboard::KeyCode::Escape))
	{
		GAME->stop();
	}

	if (INPUT->getKeyDown(Keyboard::C))
	{
		CLIENT->connect("127.0.0.1");
	}
}

void PongApp::draw()
{
	Camera* cam = GRAPHICS->getCamera();
}

void PongApp::handleEvent(const Event & ev)
{
}