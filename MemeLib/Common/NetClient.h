#ifndef _NET_CLIENT_H_
#define _NET_CLIENT_H_

#include <cassert>
#include <string>
#include <RakPeerInterface.h>
#include <MessageIdentifiers.h>
#include <RakNetTypes.h>
#include <BitStream.h>
#include "LinkingContext.h"
#include "ObjectCreationRegistry.h"
#include "GameObjectManager.h"

#define CLIENT NetClient::getInstance()

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

	void connect(const std::string address);
	bool isConnected() const;
	void writeStateToFile(int clientNum);
private:
	NetClient();
	~NetClient();

	RakNet::RakPeerInterface* mp_peer;
	RakNet::Packet*	mp_packet;
	LinkingContext* mLinkContext;
	bool	m_isConnected;
	static NetClient* sp_instance;
};

#endif // !_NET_CLIENT_H_
