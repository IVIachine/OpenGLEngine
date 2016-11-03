#ifndef LINKING_CONTEXT_H
#define LINKING_CONTEXT_H
#include <Trackable.h>
#include "GameObject.h"
#include <algorithm>
#include <unordered_map>
#include <MessageIdentifiers.h>
#include <cassert>

enum GameMessages
{
	REPLICATION_PACKET = ID_USER_PACKET_ENUM + 1,
};

#define LINKING LinkingContext::getInstance()

class LinkingContext : public Trackable
{
public:
	static LinkingContext*	getInstance()
	{
		assert(sp_instance != NULL);
		return sp_instance;
	};
	static LinkingContext*	createInstance()
	{
		sp_instance = new LinkingContext();
		return getInstance();
	};
	static void		destroyInstance()
	{
		delete sp_instance;
		sp_instance = NULL;
	};

	uint32_t GetNetworkId(GameObject* inGameObject, bool inShouldCreateIfNotFound);
	void AddGameObject(GameObject* inGameObject, uint32_t inNetworkId);
	void RemoveGameObject(GameObject *inGameObject);
	GameObject* getGameObject(uint32_t netId, bool inShouldCreateIfNotFound, uint32_t classId);

private:
	std::unordered_map<uint32_t, GameObject*> mNetworkIdToGameObjectMap;
	std::unordered_map<const GameObject*, uint32_t> mGameObjectToNetworkIdMap;
	uint32_t mNextNetworkId;
	LinkingContext() : mNextNetworkId(1) {}
	~LinkingContext() {};

	static LinkingContext* sp_instance;
};
#endif
