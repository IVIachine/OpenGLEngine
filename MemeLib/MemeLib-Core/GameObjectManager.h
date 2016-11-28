#ifndef _GAME_OBJECT_MANAGER_H_
#define _GAME_OBJECT_MANAGER_H_

#include <MemoryPool.h>
#include "GameObject.h"
#include <map>
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
	static void					destroyInstance()
	{
		delete sp_instance;
		sp_instance = NULL;
	};

	bool	setup();
	void	clear();	
	void	update();
	void	draw();

	std::map<GameObjectID, GameObject*> getData() const { return m_objectMap; };

	GameObject*	create(GameObject* obj, GameObjectID id = INVALID_GOBJ_ID);
	GameObject* findByID(GameObjectID index);

	bool		removeByID(GameObjectID index);
	size_t		size();


	template <typename T>
	T* create(GameObject* obj, GameObjectID id)
	{
		if (T* tmp = static_cast<T*>(create(obj, id)))
		{
			return tmp;
		}

		return NULL;
	};

	template <typename T>
	T* findByID(GameObjectID id)
	{ 
		if (T* tmp = static_cast<T*>(findByID(id)))
		{
			return tmp;
		}

		return NULL;
	};

	template <typename T>
	std::vector<T*> findObjectsOfType()
	{
		std::vector<T*> list;

		for (auto& pair : m_objectMap)
		{
			if (T* tmp = dynamic_cast<T*>(pair.second))
			{
				list.push_back(tmp);
			}
		}

		return list;
	};

private:
	GameObjectManager();
	~GameObjectManager();

	std::map<GameObjectID, GameObject*> m_objectMap;
	GameObjectID m_id = INVALID_GOBJ_ID;

	static GameObjectManager* sp_instance;
};
#endif // !_GAME_OBJECT_MANAGER_H_
