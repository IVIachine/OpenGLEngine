#include "GameObjectManager.h"
#include <algorithm>

GameObjectManager* GameObjectManager::sp_instance = NULL;

GameObjectManager::GameObjectManager()
{
}

GameObjectManager::~GameObjectManager()
{
	cleanup();
}


bool GameObjectManager::setup()
{
	std::cout << toString() << " -> SETUP\n";

	return true;
}

void GameObjectManager::cleanup()
{
	for (auto& pair : m_objectMap)
	{
		delete pair.second;
		pair.second = NULL;
	}
	m_objectMap.clear();
}


void GameObjectManager::update()
{
	for (auto& pair : m_objectMap)
	{
		pair.second->update();
	}
}

void GameObjectManager::draw()
{
	for (auto& pair : m_objectMap)
	{
		pair.second->draw();
	}
}


GameObject* GameObjectManager::create(GameObject* obj)
{
	if (!findByID(obj->getID()))
	{
		m_id++;
		m_objectMap[m_id] = obj;
		m_objectMap[m_id]->setID(m_id);

		m_objectMap[m_id]->start();

		return m_objectMap[m_id];
	}

	return NULL;
}

GameObject* GameObjectManager::findByID(GameObjectID id)
{
	if (id != INVALID_GOBJ_ID)
	{
		for (auto& pair : m_objectMap)
		{
			if (pair.first == id)
			{
				return m_objectMap[id];
			}
		}
	}

	return NULL;
}

bool GameObjectManager::removeByID(GameObjectID id)
{
	if (findByID(id) != NULL)
	{
		m_objectMap[id]->destroy();

		delete m_objectMap[id];

		m_objectMap[id] = NULL;

		m_objectMap.erase(id);

		return true;
	}

	return false;
}

size_t GameObjectManager::size()
{
	return m_objectMap.size();
}