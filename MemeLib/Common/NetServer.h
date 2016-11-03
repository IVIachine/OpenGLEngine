#ifndef _NET_SERVER_H_
#define _NET_SERVER_H_

#include <map>
#include <cassert>
#include <RakPeerInterface.h>
#include <MessageIdentifiers.h>
#include <RakNetTypes.h>
#include <BitStream.h>
#include "LinkingContext.h"
#include "ObjectCreationRegistry.h"
#include "GameObjectManager.h"
#include "Archer.h"
#include "TownCenter.h"

#define SERVER NetServer::getInstance()

#define SERVER_PORT 25566
#define MAX_CLIENTS 10

class NetServer
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

private:
	NetServer();
	~NetServer();

	RakNet::RakPeerInterface* mp_peer;
	RakNet::Packet*	mp_packet;
	LinkingContext* mLinkContext;
	GameObjectManager* mManager;

	static NetServer* sp_instance;
};



#endif // !_NET_SERVER_H_
