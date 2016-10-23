#ifndef _TIME_H_
#define _TIME_H_

#include <cassert>
#include <Trackable.h>
#include <Timer.h>

#define TIME Time::getInstance()

typedef unsigned int uint;

class Time : public Trackable
{
public:
	static Time*	getInstance()
	{
		assert(sp_instance != NULL);
		return sp_instance;
	};
	static void		destroyInstance()
	{
		delete sp_instance;
		sp_instance = NULL;
	};
	static Time*	createInstance()
	{
		sp_instance = new Time();
		return getInstance();
	};


	bool	setup();
	void	cleanup();

	void	beginStep();
	void	step();
	void	endStep();

	double	deltaTime();
	int		elapsedMilliseconds();
	uint	frameRate();

	/*	Constants
	* * * * * * * * * * * * */
	static const float FPS_15;
	static const float FPS_30;
	static const float FPS_60;

private:
	Time();
	~Time();

	Timer m_timer;
	double
		startTime,
		totalTime,
		endTime,
		delta;

	static Time* sp_instance;
};

#endif // !_TIME_H_
