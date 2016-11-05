// NYI

#ifndef _GAME_OBJECT_MANAGER_H_
#define _GAME_OBJECT_MANAGER_H_

#include "GameObject.h"
#include <vector>
#include <Trackable.h>

#define OBJECT_MANAGER GameObjectManager::getInstance()

class GameObjectManager: public Trackable
{
public:
	static GameObjectManager*	getInstance()
	{
		assert(sp_instance != NULL);
		return sp_instance;
	};
	static GameObjectManager*	createInstance()
	{
		sp_instance = new GameObjectManager();
		return getInstance();
	};
	static void		destroyInstance()
	{
		delete sp_instance;
		sp_instance = NULL;
	};

	GameObject* getAtIndex(int index);
	void addObject(GameObject* toBeAdded);

	size_t getNumUnits();
	void removeUnitAtIndex(int index);
	void cleanup();
	bool objectExists(GameObject* key);
private:
	GameObjectManager();
	~GameObjectManager();
	std::vector<GameObject*> mGameObjects;

	static GameObjectManager* sp_instance;
};

#endif // !_GAME_OBJECT_MANAGER_H_
