#include "RPCManager.h"

RPCManager* RPCManager::sp_instance = NULL;

RPCManager::RPCManager()
{
}

RPCManager::~RPCManager()
{
	cleanup();
}


bool RPCManager::setup()
{
	ObjectCreationRegistry::createInstance();
	LinkingContext::createInstance();
	GameObjectManager::createInstance();

	return true;
}

void RPCManager::cleanup()
{
	ObjectCreationRegistry::destroyInstance();
	LinkingContext::destroyInstance();
	GameObjectManager::destroyInstance();
}


void RPCManager::registerUnwrapFunction(RPC_ID id, RPCReadFunc func)
{
	assert(m_rpcMap.find(id) == m_rpcMap.end());

	m_rpcMap[id] = func;
}

void RPCManager::processRPC(BitStream& iStream)
{
	iStream.IgnoreBytes(sizeof(RakNet::MessageID));

	RPC_ID id;

	iStream.Read(id);

	BitStream oStream;
	oStream.Write(iStream);

	m_rpcMap[id](oStream);
}