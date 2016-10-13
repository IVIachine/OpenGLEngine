#ifndef _NET_CLIENT_H_
#define _NET_CLIENT_H_

#include "Net.h"

#define CLIENT NetClient::getInstance()

class ChatMessage;

class NetClient : public EventListener
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

	void update();
	void setup();
	virtual void handleEvent(const Event& ev);

	RakNet::SystemAddress getConnectedSystem(int index);
	void setAddress(std::string theAddress);

	void sendMessageToServer(const ChatMessage& message);
	void sendMessageToServer(const char* cstr, GameMessages messageID);

	User*	getUser() { return &m_user; };
	void	setUser(const User& value) { m_user = User(value); }

private:
	NetClient();
	~NetClient();

	RakNet::RakPeerInterface* m_peer;
	RakNet::Packet*	m_packet;
	std::string		m_address;

	User m_user;

	static NetClient* sp_instance;
};

#endif // !_NETWORKING_SYSTEM_H_