#include "GameTime.h"

GameTime* GameTime::sp_instance = NULL;

GameTime::GameTime()
{
	startTime = 0;
	totalTime = 0;
	endTime = 0;
	delta = 0;

	mp_loopTimer = new Timer();
	mp_loopTimer->start();

	mp_masterTimer = new Timer();
	mp_masterTimer->start();
}

GameTime::~GameTime()
{
	cleanup();
}


bool GameTime::setup()
{
	return true;
}

void GameTime::cleanup()
{
	delete mp_loopTimer;
	mp_loopTimer = NULL;

	delete mp_masterTimer;
	mp_masterTimer = NULL;
}


void GameTime::beginStep()
{
	startTime = endTime;
}

void GameTime::step()
{
	totalTime += mp_loopTimer->getElapsedTime();
}

void GameTime::endStep()
{
	endTime = mp_loopTimer->getElapsedTime();

	delta = (endTime - startTime);
}


float GameTime::deltaTime()
{
	return delta;
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