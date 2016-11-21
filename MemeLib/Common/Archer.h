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

class Archer : public GameObject
{
public:
	Archer();
	~Archer();

	enum { mClassId = 'ARCH' };
	virtual uint32_t getClassId() const { return mClassId; };
	static GameObject* createInstance() { return new Archer(); };

	TownCenter* getTownCenter() { return mTownCenter; };
	Vec3 getLoc() { return mLoc; };
	CurrentAction getCurrentAction() { return mCurrentAction; };
	int getHealth() { return mHealth; };

	void setCenter(TownCenter* center) { mTownCenter = center; };
	void setHealth(int health) { mHealth = health; };
	void setLoc(Vec3 loc) { mLoc = loc; };
	void setAction(CurrentAction action) { mCurrentAction = action; };

	virtual void write(RakNet::BitStream& stream) const;
	virtual void sendToServer(RakNet::BitStream & stream);
	virtual void sendToServer(RakNet::RakPeerInterface * peer);
	virtual void read(RakNet::BitStream & stream, ObjectCreationRegistry* registry);
	virtual void writeToFile(std::ofstream& of);

	std::string enumToString(CurrentAction action);
private:
	CurrentAction mCurrentAction;
	int mHealth;
	Vec3 mLoc;
	TownCenter* mTownCenter;
};
#endif
