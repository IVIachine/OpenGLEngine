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
	virtual void update(float lerpTime);

	Vec3 getLoc() const { return m_posOld; };
	void setLoc(Vec3 loc) { m_posOld = loc; };
	void setSprite(Sprite* sprite) { mp_sprite = sprite; };

private:
	float mCurrentFrame, mNumFrames;
	Sprite* mp_sprite;
	Vec3 m_posOld;
	Vec3 m_posNew;
	Vec3 m_posCurrent;
};

