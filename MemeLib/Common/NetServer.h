#ifndef _NET_SERVER_H_
#define _NET_SERVER_H_

#include "User.h"
#include <map>
#include <cassert>
#include <RakPeerInterface.h>
#include <MessageIdentifiers.h>
#include <RakNetTypes.h>
#include <BitStream.h>

#define SERVER NetServer::getInstance()

#define SERVER_PORT 25566
#define MAX_CLIENTS 10

typedef std::map<User, RakNet::RakNetGUID> UserIDMap;

static const User REMOTE("Server");

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

	UserIDMap	m_users;

	static NetServer* sp_instance;
};



#endif // !_NET_SERVER_H_
