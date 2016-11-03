#ifndef ARCHER_H
#define ARCHER_H
#include "GameObject.h"
#include "TownCenter.h"
#include <BitStream.h>
#include "LinkingContext.h"
#include "ObjectCreationRegistry.h"
#include <RakPeerInterface.h>

enum CurrentAction 
{
	INVALID_ACTION = -1,
	SHOOTING,
	IDLE,
	WALKING
};

class Archer :public GameObject
{
public:
	Archer();
	~Archer();

	enum { mClassId = 'ARCH' };
	virtual uint32_t GetClassId() const { return mClassId; };
	static GameObject* CreateInstance() { return new Archer(); };

	TownCenter* getTownCenter() { return mTownCenter; };
	CurrentAction getCurrentAction() { return mCurrentAction; };
	int getHealth() { return mHealth; };

	void setCenter(TownCenter* center) { mTownCenter = center; };
	void setHealth(int health) { mHealth = health; };
	void setAction(CurrentAction action) { mCurrentAction = action; };

	virtual void write(RakNet::BitStream& stream) const;
	virtual void send(RakNet::RakPeerInterface* peer);
	virtual void read(RakNet::BitStream& stream);
private:
	CurrentAction mCurrentAction;
	int mHealth;
	TownCenter* mTownCenter;
};
#endif
