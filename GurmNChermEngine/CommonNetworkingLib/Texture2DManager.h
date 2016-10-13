#ifndef _TEXTURE_2D_MANAGER_H_
#define _TEXTURE_2D_MANAGER_H_

#include <map>
#include <cassert>
#include "Texture2D.h"

#define TEXTURE_MANAGER Texture2DManager::getInstance()

class Texture2D;

class Texture2DManager
{
public:
	static Texture2DManager*	getInstance();
	static Texture2DManager*	createInstance();
	static void					destroyInstance();

	void		cleanup();

	Texture2D*	create(const std::string& key, int width, int height);
	Texture2D*	loadFromFile(const std::string& key, std::string filename);
	
	Texture2D*	getTexture(const std::string& key);
	Texture2D*	operator[](std::string key);

private:
	Texture2DManager();
	~Texture2DManager();

	std::map <std::string, Texture2D*> m_textureMap;

	static Texture2DManager* sp_instance;
};

#endif