#pragma once
#include "GameObject.h"
#include "Sprite.h"


class PaddleClient : public GameObject
{
public:
	PaddleClient();
	~PaddleClient();

	enum { mClassId = 'PADL' };
	virtual uint32_t getClassId() const { return mClassId; };

	virtual void write(RakNet::BitStream& stream);
	virtual void sendToServer(RakNet::BitStream & stream);
	virtual void sendToServer(RakNet::RakPeerInterface * peer);
	virtual void read(RakNet::BitStream& stream);
	virtual void writeToFile(std::ofstream& of);
	virtual void draw();
	virtual void updateClient();

	Vec3 getLoc() { return m_pos; };
	void setLoc(Vec3 loc) { m_pos = loc; };
	void setSprite(Sprite* sprite) { mp_sprite = sprite; };
	void resetPaddle() { m_dir = Vec3(0, 0, 0); };
private:
	Sprite* mp_sprite;
	Vec3 m_pos, m_dir;
	bool mFirstMove;
};

