#ifndef _PERFORMANCE_TRACKER_H_
#define _PERFORMANCE_TRACKER_H_

#include "Timer.h"

#include <map>
#include <string>
#include <Trackable.h>

class PerformanceTracker : public Trackable
{
public:
	PerformanceTracker();
	~PerformanceTracker();

	void startTracking(const std::string& trackerName);
	void stopTracking(const std::string& trackerName);
	float getElapsedTime(const std::string& trackerName);
	void removeTracker(const std::string& trackerName);
	void clearTracker(const std::string& trackerName);

private:
	std::map<std::string, Timer*> mTimers;
};

#endif // !_PERFORMANCE_TRACKER_H_
