#include "ObjectCreationRegistry.h"

ObjectCreationRegistry* ObjectCreationRegistry::sp_instance = NULL;

GameObject * ObjectCreationRegistry::CreateGameObject(uint32_t inClassId)
{
	GameObjectCreationFunc creationFunc = mNameToGameObjectCreationFunctionMap[inClassId];
	GameObject* gameObject = creationFunc();
	return gameObject;

}
