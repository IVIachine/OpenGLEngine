#pragma once
#include "GameObject.h"
#include "Vector3.h"
#include "Movelist.h"

#define MAX_PADDLE_Y 3.3f
#define MIN_PADDLE_Y -3.3f

class PaddleServer :public GameObject
{
public:
	PaddleServer();
	~PaddleServer();

	enum { mClassId = 'PADL' };
	virtual uint32_t getClassId() const { return mClassId; };

	virtual void write(RakNet::BitStream& stream);
	virtual void sendToServer(RakNet::BitStream & stream);
	virtual void sendToServer(RakNet::RakPeerInterface * peer);
	virtual void read(RakNet::BitStream& stream);
	virtual void writeToFile(std::ofstream& of);
	virtual void draw();
	void updatePaddle(MoveList& moves);

	Vec3 getLoc() const { return mLoc; };
	void setLoc(Vec3 loc) { mLoc = loc; };
private:
	Vec3 mLoc;
};

