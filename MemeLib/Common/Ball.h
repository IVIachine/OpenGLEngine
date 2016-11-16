#pragma once
#include "GameObject.h"
#include "Vector3.h"
#include "Sprite.h"
#include <RakPeerInterface.h>
#include "BallServer.h"
#include "BallClient.h"
#include "Common.h"
#include "RPCManager.h"

class Ball :public GameObject
{
public:
	Ball();
	~Ball();

	enum { mClassId = 'BALL' };
	virtual uint32_t getClassId() const { return mClassId; };
	static GameObject* createInstance() { 
		if (RPC->getServer())
		{
			return new BallServer();
		}
		else
		{
			return new BallClient();
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

