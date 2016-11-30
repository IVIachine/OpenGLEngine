#ifndef PICKUP_SPAWNER_H
#define PICKUP_SPAWNER_H

#include <Trackable.h>
#include "NavMesh.h"

class Timer;

class PickupSpawner: public Trackable
{
public:
	PickupSpawner(float timeBetween);
	~PickupSpawner();

	void update(NavMesh* navMesh);

private:
	Timer* mTimeToSpawn;
	float mBetweenTime;
};
#endif
