#ifndef TOWN_CENTER_H
#define TOWN_CENTER_H
#include "GameObject.h"
#include "Vector3.h"
#include <BitStream.h>
#include "LinkingContext.h"
#include "ObjectCreationRegistry.h"

enum MonsterType
{
	INVALID_TYPE = -1,
	WEREWOLVES,
	ELVES,
	VAMPIRES,
	ORCS
};

class TownCenter :public GameObject
{
public:
	TownCenter();
	~TownCenter();

	enum { mClassId = 'TWNC' };

	virtual uint32_t	getClassId() const { return mClassId; };
	static GameObject*	createInstance() { return new TownCenter(); };

	MonsterType getType()	{ return mType; };
	Vec3		getLoc()	{ return mLoc; };
	int			getHealth() { return mHealth; };

	void setType(MonsterType theType) { mType = theType; };
	void setLoc(Vec3 loc) { mLoc = loc; };
	void setHealth(int health) { mHealth = health; };

	virtual void write(RakNet::BitStream& stream) const;
	virtual void sendToServer(RakNet::RakPeerInterface* peer);
	virtual void sendToServer(RakNet::BitStream& stream);
	virtual void read(RakNet::BitStream& stream);
	virtual void writeToFile(std::ofstream& of);

	std::string enumToString(MonsterType monster);

private:
	MonsterType mType;
	Vec3 mLoc;
	int mHealth;
};
#endif
