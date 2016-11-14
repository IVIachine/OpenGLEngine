#include "RPCManager.h"

RPCManager* RPCManager::sp_instance = NULL;

RPCManager::RPCManager()
{
}

RPCManager::~RPCManager()
{
	clear();
}


bool RPCManager::setup()
{
	ObjectCreationRegistry::createInstance();
	LinkingContext::createInstance();

	return true;
}

void RPCManager::clear()
{
	ObjectCreationRegistry::destroyInstance();
	LinkingContext::destroyInstance();
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
