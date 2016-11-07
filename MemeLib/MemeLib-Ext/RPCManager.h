#ifndef _RPC_MANAGER_H_
#define _RPC_MANAGER_H_

#include <unordered_map>
#include <cassert>
#include "Trackable.h"

#include "LinkingContext.h"
#include "ObjectCreationRegistry.h"
#include "GameObjectManager.h"

#define RPC RPCManager::getInstance()

typedef int RPC_ID;
typedef RakNet::BitStream BitStream;
typedef void (*RPCReadFunc) (BitStream&);

class RPCManager : public Trackable
{
public:
	static RPCManager*	getInstance()
	{
		assert(sp_instance != NULL);
		return sp_instance;
	};
	static RPCManager*	createInstance()
	{
		sp_instance = new RPCManager();
		return getInstance();
	};
	static void			destroyInstance()
	{
		delete sp_instance;
		sp_instance = NULL;
	};

	bool setup();
	void cleanup();

	void registerUnwrapFunction(RPC_ID id, RPCReadFunc func);

	void processRPC(BitStream& iStream);

private:
	RPCManager();
	~RPCManager();

	std::unordered_map<RPC_ID, RPCReadFunc> m_rpcMap;

	static RPCManager* sp_instance;

};



#endif // !_RPC_MANAGER_H_
