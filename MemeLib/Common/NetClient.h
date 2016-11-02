#ifndef _NET_CLIENT_H_
#define _NET_CLIENT_H_

#include "User.h"
#include <cassert>
#include <string>
#include <RakPeerInterface.h>
#include <MessageIdentifiers.h>
#include <RakNetTypes.h>
#include <BitStream.h>

#define CLIENT NetClient::getInstance()

static const User LOCAL("System");

class NetClient
{
public:
	static NetClient*	getInstance()
	{
		assert(sp_instance != NULL);
		return sp_instance;
	};
	static NetClient*	createInstance()
	{
		sp_instance = new NetClient();
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
	NetClient();
	~NetClient();

	RakNet::RakPeerInterface* mp_peer;
	RakNet::Packet*	mp_packet;

	User	m_user;
	bool	m_isConnected;

	static NetClient* sp_instance;
};

#endif // !_NET_CLIENT_H_
