#ifndef _NET_SERVER_H_
#define _NET_SERVER_H_

#include "Net.h"

#define SERVER NetServer::getInstance()

class NetServer : public EventListener
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

	void update();
	void setup();
	virtual void handleEvent(const Event& ev);

	bool isRunning() const;
	void start();
	void stop();

	void sendMessage(std::string, size_t clientID);
	void broadcastMessage(std::string message);

private:
	NetServer();
	~NetServer();

	RakNet::RakPeerInterface*	m_peer;
	RakNet::Packet*				m_packet;
	
	size_t	m_numClients;
	bool	m_isRunning;

	static NetServer* sp_instance;
};

#endif // !_NETWORKING_SYSTEM_H_