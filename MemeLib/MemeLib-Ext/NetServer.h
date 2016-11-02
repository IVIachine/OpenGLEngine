#ifndef _NET_SERVER_H_
#define _NET_SERVER_H_

#include <cassert>
#include <RakPeerInterface.h>
#include <MessageIdentifiers.h>
#include <RakNetTypes.h>
#include <BitStream.h>

#define SERVER NetServer::getInstance()

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

	static NetServer* sp_instance;
};



#endif // !_NET_SERVER_H_
