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
	LinkingContext::createInstance();

	return true;
}

void RPCManager::clear()
{
	LinkingContext::destroyInstance();
}


void RPCManager::registerUnwrapFunction(RPC_ID id, RPCReadFunc func)
{
	assert(m_rpcMap.find(id) == m_rpcMap.end());

	m_rpcMap[id] = func;
}

void RPCManager::process(BitStream& iStream)
{
	iStream.IgnoreBytes(sizeof(RakNet::MessageID));

	RPC_ID id;

	iStream.Read(id);

	BitStream oStream;
	oStream.Write(iStream);

	m_rpcMap[id](oStream);
}
