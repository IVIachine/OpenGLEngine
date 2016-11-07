#ifndef _NET_SERVER_H_
#define _NET_SERVER_H_

#include <map>
#include <cassert>
#include <RakPeerInterface.h>
#include <MessageIdentifiers.h>
#include <RakNetTypes.h>
#include <BitStream.h>

#include "RPCManager.h"
#include "Archer.h"
#include "TownCenter.h"

#define SERVER NetServer::getInstance()

#define SERVER_PORT 25566
#define MAX_CLIENTS 10

class NetServer : public Trackable
{
public:
	static NetServer*	getInstance()
	{
		assert(sp_instance != NULL);
		return sp_instance;
	};
	static NetServer*	createInstance()
	{
		sp_instance = new NetServer();
		return getInstance();
	};
	static void			destroyInstance()
	{
		delete sp_instance;
		sp_instance = NULL;
	};

	bool setup();
	void cleanup();
	void update();
	void generateState();

	bool sendByAddress(RakNet::AddressOrGUID addr, BitStream& stream);
	bool sendByGuid(RakNet::RakNetGUID guid, BitStream& stream);
	bool sendByIndex(size_t index, BitStream& stream);

private:
	NetServer();
	~NetServer();

	RakNet::RakPeerInterface* mp_peer;
	RakNet::Packet*	mp_packet;
	static NetServer* sp_instance;

	size_t m_numClients = 0;
};



#endif // !_NET_SERVER_H_
