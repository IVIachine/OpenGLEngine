#ifndef _TIMER_H_
#define _TIMER_H_

#include <windows.h>
#include <Trackable.h>

/* Timer - high accuracy timer - uses Large Integer to prevent rollover

Dean Lawson
Champlain College
2011
*/

class Timer :public Trackable
{
public:
	Timer();
	~Timer();

	void start();
	void stop();
	void pause(bool shouldPause);

	float getElapsedTime() const;//returns how much time has elapsed since start
	void sleepUntilElapsed(float ms);
	
	inline float getFactor() const { return mFactor; };
	inline void multFactor(float mult) { mLastFactor = mFactor; mFactor *= mult; };
	inline void setFactor(float theFactor) { mLastFactor = mFactor; mFactor = theFactor; };
	inline void restoreLastFactor() { mFactor = mLastFactor; };

private:
	LARGE_INTEGER mStartTime;
	LARGE_INTEGER mEndTime;
	LARGE_INTEGER mTimerFrequency;
	float mElapsedTime;
	float mFactor;
	float mLastFactor;
	bool mPaused;

	//helper function - uses current frequency for the Timer
	float calcDifferenceInMS(LARGE_INTEGER from, LARGE_INTEGER to) const;

};

#endif // !_TIMER_H_
