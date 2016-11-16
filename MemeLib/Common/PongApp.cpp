#include "PongApp.h"
#include <Input.h>
#include <Gizmos.h>
#include <EventSystem.h>
#include <GameObjectManager.h>
#include <ResourceManager.h>

PongApp::PongApp()
{
}

PongApp::~PongApp()
{
}


bool PongApp::setup()
{
	GRAPHICS->getCamera()->setPosition({ 0, 0, -10 });
	GRAPHICS->getCamera()->setForward({ 0, 0, 1 });
	GRAPHICS->enableMouseLook(false);

	Shader* p_shader = RESOURCES->addShader("basic", "../Assets/shaders/basicShader");

	RESOURCES->addTexture("paddle1", "../Assets/textures/Pong/paddleBlue.png");
	RESOURCES->addTexture("paddle2", "../Assets/textures/Pong/paddleRed.png");
	RESOURCES->addTexture("ball", "../Assets/textures/Pong/ball.png");

	RESOURCES->addTexture2D("paddle1", RESOURCES->getTexture("paddle1"), p_shader);
	RESOURCES->addTexture2D("paddle2", RESOURCES->getTexture("paddle2"), p_shader);
	RESOURCES->addTexture2D("ball", RESOURCES->getTexture("ball"), p_shader);

	RESOURCES->addSprite("paddle1", RESOURCES->getTexture2D("paddle1"));
	RESOURCES->addSprite("paddle2", RESOURCES->getTexture2D("paddle2"));
	RESOURCES->addSprite("ball", RESOURCES->getTexture2D("ball"));

	m_paddle1.sprite = RESOURCES->getSprite("paddle1");
	m_paddle1.sprite->setScale(Vec3(0.25f, 1.0f, 0.25f));
	m_paddle1.sprite->setRotation(Vec3(0, 180, 0) * Maths::DEG_TO_RAD);

	m_paddle2.sprite = RESOURCES->getSprite("paddle2");
	m_paddle2.sprite->setScale(Vec3(0.25f, 1.0f, 0.25f));
	m_paddle2.sprite->setRotation(Vec3(0, 180, 0) * Maths::DEG_TO_RAD);

	m_ball.sprite = RESOURCES->getSprite("ball");
	m_ball.sprite->setScale(Vec3(0.25f, 0.25f, 0.25f));
	m_ball.sprite->setRotation(Vec3(0, 180, 0) * Maths::DEG_TO_RAD);

	m_paddle1.position = Vec3(0.f, 0.f, 0.f);
	m_paddle2.position = Vec3(0.f, 0.f, 0.f);
	m_ball.position = Vec3(0.f, 0.f, 0.f);

	return true;
}

void PongApp::clear()
{
}

void PongApp::update()
{
	Camera* cam = GRAPHICS->getCamera();

	m_paddle1.position = { -1, 0, 0 };
	m_paddle2.position = { 1, 0, 0 };
	m_ball.position = { 0, 0, 0 };

	m_paddle1.sprite->setPosition(m_paddle1.position);
	m_paddle2.sprite->setPosition(m_paddle2.position);
	m_ball.sprite->setPosition(m_ball.position);

	if (INPUT->getKeyDown(Keyboard::KeyCode::Escape))
	{
		GAME->stop();
	}
}

void PongApp::draw()
{
	Camera* cam = GRAPHICS->getCamera();

	m_paddle1.sprite->draw(*cam);
	m_paddle2.sprite->draw(*cam);
	m_ball.sprite->draw(*cam);
}

void PongApp::handleEvent(const Event & ev)
{
}