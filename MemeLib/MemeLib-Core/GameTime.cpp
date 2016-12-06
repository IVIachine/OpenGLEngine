#include "GameTime.h"

GameTime* GameTime::sp_instance = NULL;

GameTime::GameTime()
{
}

GameTime::~GameTime()
{
	clear();
}


bool GameTime::setup()
{
	m_startTime = 0;
	m_totalTime = 0;
	m_endTime = 0;
	m_delta = 0;

	mp_loopTimer = new Timer();
	mp_loopTimer->start();

	mp_masterTimer = new Timer();
	mp_masterTimer->start();

	return true;
}

void GameTime::clear()
{
	delete mp_loopTimer;
	mp_loopTimer = NULL;

	delete mp_masterTimer;
	mp_masterTimer = NULL;
}


void GameTime::beginStep()
{
	m_startTime = m_endTime;
}

void GameTime::step()
{
	m_totalTime = mp_masterTimer->getElapsedTime();
}

void GameTime::endStep()
{
	m_endTime = mp_loopTimer->getElapsedTime();

	m_delta = (m_endTime - m_startTime);
}


float GameTime::deltaTime()
{
	return m_delta;
}

int GameTime::elapsedMilliseconds()
{
	return int(deltaTime());
}

uint GameTime::frameRate()
{
	/*
	http://en.sfml-dev.org/forums/index.php?topic=6090.0
	FPS calculations with SFML2.0
	Mars_999
	*/

	static unsigned int
		frameCounter = 0,
		fps = 0;

	static float
		nextSecond = 0.0f,
		prevSecond = 0.0f;

	frameCounter++;

	nextSecond += (float)(deltaTime() * 0.001f);

	//std::cout << nextSecond << std::endl;

	if (nextSecond - prevSecond > 1.0f)
	{
		prevSecond = nextSecond;
		fps = frameCounter;
		frameCounter = 0;
	}

	return fps;
}


/*	Constants
* * * * * * * * * * * * */
const float GameTime::FPS_15 = 66.666f;
const float GameTime::FPS_30 = 33.333f;	// 30fps = 33.3ms/frame
const float GameTime::FPS_60 = 16.666f;