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

	RESOURCES->addTexture("bg", "../Assets/textures/Pong/bg.jpg");
	RESOURCES->addTexture("paddle1", "../Assets/textures/Pong/paddleBlue.png");
	RESOURCES->addTexture("ball", "../Assets/textures/Pong/ballGrey.png");

	RESOURCES->addTexture2D("bg", RESOURCES->getTexture("bg"), p_shader);
	RESOURCES->addTexture2D("paddle1", RESOURCES->getTexture("paddle1"), p_shader);
	RESOURCES->addTexture2D("ball", RESOURCES->getTexture("ball"), p_shader);

	RESOURCES->addSprite("bg", RESOURCES->getTexture2D("bg"));
	RESOURCES->addSprite("paddle1", RESOURCES->getTexture2D("paddle1"));
	RESOURCES->addSprite("ball", RESOURCES->getTexture2D("ball"));

	mp_bg = RESOURCES->getSprite("bg");
	mp_bg->setScale(Vec3(10.f, 5.f, 1.f));
	mp_bg->setRotation(Vec3(0.f, 180.f, 0.f) * Maths::DEG_TO_RAD);
	mp_bg->setPosition(Vec3(0.f, 0.f, 1.f));

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

	if (!CLIENT->isConnected())
	{
		if (INPUT->getKeyDown(Keyboard::C))
		{
			std::cout << "Connecting to server... \n";
			CLIENT->connect(m_ip);
		}
	}
}

void PongApp::draw()
{
	Camera* cam = GRAPHICS->getCamera();

	mp_bg->draw(*cam);
}

void PongApp::handleEvent(const Event & ev)
{
}