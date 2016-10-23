#include "Time.h"

Time* Time::sp_instance = NULL;

Time::Time()
{
	startTime = 0;
	totalTime = 0;
	endTime = 0;
	delta = 0;

	m_timer = Timer();
	m_timer.start();
}

Time::~Time()
{
	cleanup();
}


bool Time::setup()
{
	return true;
}

void Time::cleanup()
{

}


void Time::beginStep()
{
	startTime = endTime;
}

void Time::step()
{
	totalTime = m_timer.getElapsedTime();
}

void Time::endStep()
{
	endTime = m_timer.getElapsedTime();

	delta = (endTime - startTime);
}


double Time::deltaTime()
{
	return delta;
}

int Time::elapsedMilliseconds()
{
	return int(deltaTime());
}

uint Time::frameRate()
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
const float Time::FPS_15 = 66.666f;
const float Time::FPS_30 = 33.333f;	// 30fps = 33.3ms/frame
const float Time::FPS_60 = 16.666f;