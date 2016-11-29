#include "PickupSpawner.h"
#include "Pickup.h"
#include "GameObjectManager.h"
#include <Timer.h>

PickupSpawner::PickupSpawner(float timeBetween)
{
	mTimeToSpawn = new Timer();
	mBetweenTime = timeBetween;
	mTimeToSpawn->start();
}


PickupSpawner::~PickupSpawner()
{
	delete mTimeToSpawn;
	mTimeToSpawn = NULL;
}

void PickupSpawner::update()
{
	if (mTimeToSpawn->getElapsedTime() >= mBetweenTime)
	{
		mTimeToSpawn->stop();
		Pickup* newPickup = OBJECT_MANAGER->create<Pickup>(new Pickup(Vec3(0, 0, 0), PickupType::SPEED_TYPE));
		mTimeToSpawn->start();
	}
}
