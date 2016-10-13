#include "Texture2DManager.h"

Texture2DManager* Texture2DManager::sp_instance = NULL;

Texture2DManager::Texture2DManager()
{
}

Texture2DManager::~Texture2DManager()
{
	cleanup();
}


Texture2DManager* Texture2DManager::getInstance()
{
	assert(sp_instance != NULL);
	return sp_instance;
}

void Texture2DManager::destroyInstance()
{
	delete sp_instance;
	sp_instance = NULL;
}

Texture2DManager* Texture2DManager::createInstance()
{
	sp_instance = new Texture2DManager();
	return getInstance();
}


void Texture2DManager::cleanup()
{
	//go through all entries in map and delete
	
	std::map<std::string, Texture2D*>::iterator iter;

	for (iter = m_textureMap.begin(); iter != m_textureMap.end(); ++iter)
	{
		Texture2D* pGraphicsBuffer = iter->second;
		delete pGraphicsBuffer;
	}

	m_textureMap.clear();
}


Texture2D* Texture2DManager::loadFromFile(const std::string& key, std::string filename)
{
	std::map<std::string, Texture2D*>::iterator found = m_textureMap.find(key);
	if (found == m_textureMap.end())
	{
		m_textureMap[key] = new Texture2D(filename);
	}

	return NULL;
}

Texture2D* Texture2DManager::create(const std::string& key, int width, int height)
{
	std::map<std::string, Texture2D*>::iterator found = m_textureMap.find(key);
	if (found == m_textureMap.end())
	{
		m_textureMap[key] = new Texture2D(width, height);
	}

	return NULL;
}


Texture2D* Texture2DManager::getTexture(const std::string& key)
{
	std::map<std::string, Texture2D*>::const_iterator found = m_textureMap.find(key);
	if (found != m_textureMap.end())
	{
		return found->second;
	}
	else
	{
		return NULL;
	}
}

Texture2D* Texture2DManager::operator[](std::string key)
{
	return getTexture(key);
}