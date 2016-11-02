#ifndef NETWORK_H
#define NETWORK_H
#include <RakPeerInterface.h>
#include <MessageIdentifiers.h>
#include <BitStream.h>
#include <RakNetTypes.h>
#include <Trackable.h>
#define NETWORK Network::getInstance()

class Network:public Trackable
{
public:
	static Network*	getInstance()
	{
		assert(sp_instance != NULL);
		return sp_instance;
	};
	static Network*	createInstance()
	{
		sp_instance = new Network();
		return getInstance();
	};
	static void		destroyInstance()
	{
		delete sp_instance;
		sp_instance = NULL;
	};
	void update();

private:
	Network() {};
	~Network() {};

	static Network* sp_instance;
};
#endif
