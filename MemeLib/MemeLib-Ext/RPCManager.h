#ifndef _RPC_MANAGER_H_
#define _RPC_MANAGER_H_

#include <unordered_map>
#include <cassert>
#include "Trackable.h"

#include "Net.h"

#define RPC RPCManager::getInstance()

typedef int RPC_ID;
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
	void clear();

	void registerUnwrapFunction(RPC_ID id, RPCReadFunc func);

	void process(BitStream& iStream);
	bool getServer() { return m_isServer; };
	void setServer(bool server) { m_isServer = server; };
private:
	RPCManager();
	~RPCManager();

	std::unordered_map<RPC_ID, RPCReadFunc> m_rpcMap;
	bool m_isServer;
	static RPCManager* sp_instance;

};



#endif // !_RPC_MANAGER_H_
