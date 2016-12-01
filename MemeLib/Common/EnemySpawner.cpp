#include "EnemySpawner.h"
#include "Pickup.h"
#include "GameObjectManager.h"
#include <Timer.h>
#include "UnitManager.h"
#include "ResourceManager.h"

EnemySpawner::EnemySpawner(float timeBetween, Vec3 spawnLoc)
{
	mTimeToSpawn = new Timer();
	mBetweenTime = timeBetween;
	mSpawnLoc = spawnLoc;
	mTimeToSpawn->start();
}


EnemySpawner::~EnemySpawner()
{
	delete mTimeToSpawn;
	mTimeToSpawn = NULL;
}

void EnemySpawner::update(NavMesh* navMesh)
{
	if (mTimeToSpawn->getElapsedTime() >= mBetweenTime)
	{
		mTimeToSpawn->stop();		
		Unit* pUnit = UNITS->createUnit(
			*RESOURCES->getSprite("idle"),
			navMesh,
			200,
			1,
			.1,
			true,
			PositionData(mSpawnLoc, 0));

		pUnit->setSteering(Steering::PATH_FOLLOW);
		mTimeToSpawn->start();
	}
}
