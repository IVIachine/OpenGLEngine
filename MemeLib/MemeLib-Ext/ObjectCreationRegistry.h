#ifndef OBJECT_CREATION_REGISTRY
#define OBJECT_CREATION_REGISTRY
#include <unordered_map>
#include "GameObject.h"
#include <Trackable.h>
#include <algorithm>
#include <cassert>

typedef GameObject* (*GameObjectCreationFunc)();

class ObjectCreationRegistry : public Trackable
{
public:
	ObjectCreationRegistry() {}
	~ObjectCreationRegistry() {};

	template<class T>
	void RegisterCreationFunction()
	{ 
		assert(mNameToGameObjectCreationFunctionMap.find(T::mClassId) == mNameToGameObjectCreationFunctionMap.end());
		mNameToGameObjectCreationFunctionMap[T::mClassId] = T::createInstance;
	}

	GameObject* CreateGameObject(uint32_t inClassId);
private:
	std::unordered_map<uint32_t, GameObjectCreationFunc> mNameToGameObjectCreationFunctionMap;
};
#endif
