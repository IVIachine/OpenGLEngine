#include "GameObjectManager.h"

GameObjectManager* GameObjectManager::sp_instance = NULL;

GameObjectManager::GameObjectManager()
{
}

GameObjectManager::~GameObjectManager()
{
	cleanup();
}

GameObject * GameObjectManager::getAtIndex(int index)
{
	return mGameObjects[index];
}

void GameObjectManager::addObject(GameObject * toBeAdded)
{
	mGameObjects.push_back(toBeAdded);
}

size_t GameObjectManager::getNumUnits()
{
	return mGameObjects.size();
}

void GameObjectManager::removeUnitAtIndex(int index)
{
	delete mGameObjects[index];
	mGameObjects.erase(mGameObjects.begin() + index);
}

void GameObjectManager::cleanup()
{
	while (!mGameObjects.empty()) delete mGameObjects.back(), mGameObjects.pop_back();
}

bool GameObjectManager::objectExists(GameObject * key)
{
	for (size_t i = 0; i < mGameObjects.size(); i++)
	{
		if (mGameObjects[i] == key)
		{
			return true;
		}
	}
	return false;
}
