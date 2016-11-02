#ifndef _NET_CLIENT_H_
#define _NET_CLIENT_H_

#include <cassert>
#include <RakPeerInterface.h>
#include <MessageIdentifiers.h>
#include <RakNetTypes.h>
#include <BitStream.h>

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

private:
	NetClient();
	~NetClient();

	static NetClient* sp_instance;

};

#endif // !_NET_CLIENT_H_
