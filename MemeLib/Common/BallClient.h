#pragma once
#include "GameObject.h"
#include "Sprite.h"

class BallClient :public GameObject
{
public:
	BallClient();
	~BallClient();

	enum { mClassId = 'BALL' };
	virtual uint32_t getClassId() const { return mClassId; };

	virtual void write(RakNet::BitStream& stream) const;
	virtual void sendToServer(RakNet::BitStream & stream);
	virtual void sendToServer(RakNet::RakPeerInterface * peer);
	virtual void read(RakNet::BitStream& stream);
	virtual void writeToFile(std::ofstream& of);
	virtual void draw();
	virtual void update();

	Vec3 getLoc() const { return mLoc; };
	void setLoc(Vec3 loc) { mLoc = loc; };
	void setSprite(Sprite* sprite) { mp_sprite = sprite; };
private:
	Sprite* mp_sprite;
	Vec3 mLoc;
};

