#ifndef _TIME_H_
#define _TIME_H_

#include <cassert>
#include <Trackable.h>
#include <Timer.h>

#define TIME GameTime::getInstance()

typedef unsigned int uint;

class GameTime : public Trackable
{
public:
	static GameTime*	getInstance()
	{
		assert(sp_instance != NULL);
		return sp_instance;
	};
	static void		destroyInstance()
	{
		delete sp_instance;
		sp_instance = NULL;
	};
	static GameTime*	createInstance()
	{
		sp_instance = new GameTime();
		return getInstance();
	};


	bool	setup();
	void	cleanup();

	void	beginStep();
	void	step();
	void	endStep();

	float	deltaTime();
	int		elapsedMilliseconds();
	uint	frameRate();

	Timer*	getMasterTimer() { return mp_masterTimer; };
	float	getCurrentTime() { return mp_masterTimer->getElapsedTime(); };

	/*	Constants
	* * * * * * * * * * * * */
	static const float FPS_15;
	static const float FPS_30;
	static const float FPS_60;

private:
	GameTime();
	~GameTime();

	Timer*	mp_loopTimer;
	Timer*	mp_masterTimer;

	float
		startTime,
		totalTime,
		endTime,
		delta;

	static GameTime* sp_instance;
};

#endif // !_TIME_H_