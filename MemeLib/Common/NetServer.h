#ifndef _NET_SERVER_H_
#define _NET_SERVER_H_

#include "Net.h"
#include "Archer.h"
#include "TownCenter.h"
#include "Paddle.h"
#include "Ball.h"

#define SERVER NetServer::getInstance()

#define SERVER_PORT 25566
#define MAX_CLIENTS 2

class ClientProxy;

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

	void handleNewClient(BitStream& iStream, NetAddress addr);

	bool setup();
	void clear();
	void update();
	
	bool sendByAddress(NetAddress addr, BitStream& stream);
	bool sendByGuid(NetGUID guid, BitStream& stream);
	bool sendByIndex(size_t index, BitStream& stream);

	void generateState();
	void broadcastNewLocation(PaddleServer* key);

private:
	NetServer();
	~NetServer();

	RakNet::RakPeerInterface* mp_peer;
	RakNet::Packet*	mp_packet;
	static NetServer* sp_instance;
	std::map<NetAddress, ClientProxy> m_clients;

	BallServer* m_ball;
	PaddleServer* m_paddleL;
	PaddleServer* m_paddleR;
	int m_frameCounter;
	int m_pointsR, m_pointsL;

	//size_t m_numClients = 0;
};



#endif // !_NET_SERVER_H_
