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

void PickupSpawner::update(NavMesh* navMesh)
{
	if (mTimeToSpawn->getElapsedTime() >= mBetweenTime)
	{
		mTimeToSpawn->stop();
		int randNodeIndex = rand() % (navMesh->getVerts().size() - 1);
		int randType = rand() % ((int)NUM_PICKUP_TYPES);
		std::cout << navMesh->getVerts().at(randNodeIndex).y << std::endl;
		Pickup* newPickup = OBJECT_MANAGER->create<Pickup>(new Pickup(navMesh->getVerts().at(randNodeIndex), PickupType(randType)));
		mTimeToSpawn->start();
	}
}
