#ifndef _RESOURCE_MANAGER_H_
#define _RESOURCE_MANAGER_H_

#include <cassert>
#include "Dictionary.h"

class Font;
class Texture;
class Texture2D;
class Shader;
class Sprite;

#define RESOURCES ResourceManager::getInstance()

typedef std::string TKey;

class ResourceManager
{
public:
	static ResourceManager*	getInstance()
	{
		assert(sp_instance != NULL);
		return sp_instance;
	};
	static ResourceManager*	createInstance()
	{
		sp_instance = new ResourceManager();
		return getInstance();
	};
	static void		destroyInstance()
	{
		delete sp_instance;
		sp_instance = NULL;
	};

	bool setup();
	void cleanup();

	Font*		addFont(TKey key, const std::string& filename);
	Font*		getFont(TKey key);
	Font*		setFont(TKey key, const std::string& filename);

	Texture*	addTexture(TKey key, const std::string& filename);
	Texture*	getTexture(TKey key);
	Texture*	setTexture(TKey key, const std::string& filename);

	Texture2D*	addTexture2D(TKey key, Texture* texture, Shader* shader);
	Texture2D*	getTexture2D(TKey key);
	Texture2D*	setTexture2D(TKey key, Texture* texture, Shader* shader);

	Shader*		addShader(TKey key, const std::string& filename);
	Shader*		getShader(TKey key);
	Shader*		setShader(TKey key, const std::string& filename);

	Sprite*		addSprite(TKey key, Texture2D* texture2D);
	Sprite*		getSprite(TKey key);
	Sprite*		setSprite(TKey key, Texture2D* texture2D);

private:
	Dictionary<TKey, Font>		m_fonts;
	Dictionary<TKey, Texture>	m_textures;
	Dictionary<TKey, Texture2D> m_texture2Ds;
	Dictionary<TKey, Shader>	m_shaders;
	Dictionary<TKey, Sprite>	m_sprites;

	ResourceManager();
	~ResourceManager();

	static ResourceManager* sp_instance;
};

#endif // !_RESOURCE_MANAGER_H_
