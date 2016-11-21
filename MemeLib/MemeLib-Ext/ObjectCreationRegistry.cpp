#include "ObjectCreationRegistry.h"

GameObject * ObjectCreationRegistry::CreateGameObject(uint32_t inClassId)
{
	GameObjectCreationFunc creationFunc = mNameToGameObjectCreationFunctionMap[inClassId];
	GameObject* gameObject = creationFunc();
	return gameObject;
}
