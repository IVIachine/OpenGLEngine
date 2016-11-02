#ifndef LINKING_CONTEXT_H
#define LINKING_CONTEXT_H
#include <Trackable.h>
#include "GameObject.h"
#include <algorithm>
#include <unordered_map>

class LinkingContext : public Trackable
{
public:
	LinkingContext() : mNextNetworkId(1) {}
	~LinkingContext() {};

	uint32_t GetNetworkId(GameObject* inGameObject, bool inShouldCreateIfNotFound);
	void AddGameObject(GameObject* inGameObject, uint32_t inNetworkId);
	void RemoveGameObject(GameObject *inGameObject);

private:
	std::unordered_map<uint32_t, GameObject*> mNetworkIdToGameObjectMap;
	std::unordered_map<const GameObject*, uint32_t> mGameObjectToNetworkIdMap;
	uint32_t mNextNetworkId;
};
#endif
