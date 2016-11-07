#ifndef _NET_CLIENT_H_
#define _NET_CLIENT_H_

#include <Trackable.h>
#include <cassert>
#include <string>

#include "Net.h"

#define CLIENT NetClient::getInstance()
#define MAX_CONNECTIONS 1
#define SOCKET_DESC_COUNT 1

class NetClient : public Trackable
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
	void sendToServer(BitStream& out);

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
