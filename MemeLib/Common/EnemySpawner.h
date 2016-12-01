#ifndef ENEMY_SPAWNER_H
#define ENEMY_SPAWNER_H

#include <Trackable.h>
#include "NavMesh.h"

class Timer;

class EnemySpawner : public Trackable
{
public:
	EnemySpawner(float timeBetween, Vec3 spawnLoc);
	~EnemySpawner();

	void update(NavMesh* navMesh);

private:
	Timer* mTimeToSpawn;
	float mBetweenTime;
	Vec3 mSpawnLoc;
};
#endif
