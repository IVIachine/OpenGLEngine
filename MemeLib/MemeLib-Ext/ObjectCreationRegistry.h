#ifndef OBJECT_CREATION_REGISTRY
#define OBJECT_CREATION_REGISTRY
#include <unordered_map>
#include "GameObject.h"
#include <Trackable.h>
#include <algorithm>
#include <cassert>

typedef GameObject* (*GameObjectCreationFunc)();
#define REGISTRY ObjectCreationRegistry::getInstance()

class ObjectCreationRegistry : public Trackable
{
public:
	static ObjectCreationRegistry*	getInstance()
	{
		assert(sp_instance != NULL);
		return sp_instance;
	};
	static ObjectCreationRegistry*	createInstance()
	{
		sp_instance = new ObjectCreationRegistry();
		return getInstance();
	};
	static void		destroyInstance()
	{
		delete sp_instance;
		sp_instance = NULL;
	};

	template<class T>
	void RegisterCreationFunction()
	{ 
		assert(mNameToGameObjectCreationFunctionMap.find(T::mClassId) == mNameToGameObjectCreationFunctionMap.end());
		mNameToGameObjectCreationFunctionMap[T::mClassId] = T::CreateInstance;
	}

	GameObject* CreateGameObject(uint32_t inClassId);

private:
	ObjectCreationRegistry() {} 
	~ObjectCreationRegistry() {};
	std::unordered_map<uint32_t, GameObjectCreationFunc> mNameToGameObjectCreationFunctionMap;

	static ObjectCreationRegistry* sp_instance;
};
#endif
