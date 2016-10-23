#include "ResourceManager.h"
#include "Mesh.h"
#include "Shader.h"
#include "Texture.h"
#include "Texture2D.h"
#include "Shader.h"
#include "Sprite.h"

ResourceManager* ResourceManager::sp_instance = NULL;


ResourceManager::ResourceManager()
{
	setup();
}

ResourceManager::~ResourceManager()
{
	cleanup();
}


bool ResourceManager::setup()
{
	return true;
}

void ResourceManager::cleanup()
{
	m_shaders.cleanup();

	m_textures.cleanup();

	m_texture2Ds.cleanup();

	m_sprites.cleanup();
}


Texture* ResourceManager::addTexture(TKey key, const std::string& filename)
{
	return m_textures.addData(key, new Texture(filename));
}

Texture* ResourceManager::getTexture(TKey key)
{
	return m_textures.getData(key);
}

Texture* ResourceManager::setTexture(TKey key, const std::string& filename)
{
	return m_textures.setData(key, new Texture(filename));
}


Texture2D* ResourceManager::addTexture2D(TKey key, Texture* texture, Shader* shader)
{
	return m_texture2Ds.addData(key, new Texture2D(texture, shader));
}

Texture2D* ResourceManager::getTexture2D(TKey key)
{
	return m_texture2Ds.getData(key);
}

Texture2D* ResourceManager::setTexture2D(TKey key, Texture* texture, Shader* shader)
{
	return m_texture2Ds.setData(key, new Texture2D(texture, shader));
}


Shader* ResourceManager::addShader(TKey key, const std::string& filename)
{
	return m_shaders.addData(key, new Shader(filename));
}

Shader* ResourceManager::getShader(TKey key)
{
	return m_shaders.getData(key);
}

Shader* ResourceManager::setShader(TKey key, const std::string& filename)
{
	return m_shaders.setData(key, new Shader(filename));
}


Sprite* ResourceManager::addSprite(TKey key, Texture2D* texture2D)
{
	return m_sprites.addData(key, new Sprite(texture2D));
}

Sprite* ResourceManager::getSprite(TKey key)
{
	return m_sprites.getData(key);
}

Sprite* ResourceManager::setSprite(TKey key, Texture2D* texture2D)
{
	return m_sprites.setData(key, new Sprite(texture2D));
}