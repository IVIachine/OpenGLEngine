#ifndef _NET_CLIENT_H_
#define _NET_CLIENT_H_

#include <Trackable.h>
#include <cassert>
#include <string>
#include "ClientProxy.h"
#include "Net.h"
#include "InputState.h"
#include "MoveList.h"
#include "ObjectCreationRegistry.h"

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
	void clear();
	void update();

	void connect(const std::string address);
	bool isConnected() const;
	void sendToServer(BitStream& out);

	void writeStateToFile(int clientNum);

private:
	NetClient();
	~NetClient();

	ClientProxy m_proxy;

	RakNet::RakPeerInterface* mp_peer;
	RakNet::Packet*	mp_packet;
	LinkingContext* mLinkContext;
	bool	m_isConnected;
	static NetClient* sp_instance;
	MoveList* m_moves;
	float m_frameCount;
	ObjectCreationRegistry* m_Registry;
};

#endif // !_NET_CLIENT_H_
