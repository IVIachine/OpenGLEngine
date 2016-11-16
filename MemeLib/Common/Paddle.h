#pragma once
#include "GameObject.h"
#include "Vector3.h"
#include "Sprite.h"
#include <RakPeerInterface.h>
#include "RPCManager.h"
#include "PaddleServer.h"
#include "PaddleClient.h"

class Paddle :public GameObject
{
public:
	Paddle();
	~Paddle();

	enum { mClassId = 'PADL' };
	virtual uint32_t getClassId() const { return mClassId; };

	static GameObject* createInstance() { 
		if (RPC->getServer())
		{
			return new PaddleServer();
		} 
		else
		{
			return new PaddleClient();
		}
	};

	virtual void write(RakNet::BitStream& stream) const;
	virtual void sendToServer(RakNet::BitStream & stream);
	virtual void sendToServer(RakNet::RakPeerInterface * peer);
	virtual void read(RakNet::BitStream& stream);
	virtual void writeToFile(std::ofstream& of);
	virtual void draw();
	virtual void update();
};

