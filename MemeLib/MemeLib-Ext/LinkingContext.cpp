#include "LinkingContext.h"
#include "ObjectCreationRegistry.h"

LinkingContext* LinkingContext::sp_instance = NULL;

uint32_t LinkingContext::GetNetworkId(GameObject * inGameObject, bool inShouldCreateIfNotFound)
{
	auto it = mGameObjectToNetworkIdMap.find(inGameObject);
	if (it != mGameObjectToNetworkIdMap.end())
	{
		return it->second;
	}
	else if (inShouldCreateIfNotFound)
	{
		uint32_t newNetworkId = mNextNetworkId++;
		AddGameObject(inGameObject, newNetworkId); return newNetworkId;
	}
	else
	{
		return 0;
	}
}

void LinkingContext::AddGameObject(GameObject * inGameObject, uint32_t inNetworkId)
{
	mNetworkIdToGameObjectMap[inNetworkId] = inGameObject;
	mGameObjectToNetworkIdMap[inGameObject] = inNetworkId;
}

void LinkingContext::RemoveGameObject(GameObject * inGameObject)
{
	uint32_t networkId = mGameObjectToNetworkIdMap[inGameObject];
	mGameObjectToNetworkIdMap.erase(inGameObject);
	mNetworkIdToGameObjectMap.erase(networkId);
}

GameObject * LinkingContext::getGameObject(uint32_t netId, bool inShouldCreateIfNotFound, uint32_t classId)
{
	auto it = mNetworkIdToGameObjectMap.find(netId);
	if (it != mNetworkIdToGameObjectMap.end())
	{
		return it->second;
	}
	else if (inShouldCreateIfNotFound)
	{
		GameObject* tmp = REGISTRY->CreateGameObject(classId);
		AddGameObject(tmp, netId);
		return tmp;
	}
	else
	{
		return 0;
	}
}
