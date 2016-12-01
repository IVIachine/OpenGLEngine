#ifndef PICKUP_H
#define PICKUP_H

#include "GameObject.h"
#include "Vector3.h"
#include <Sprite.h>

class Sprite;

enum PickupType
{
	INVALID_PICKUP_TYPE = -1,
	SPEED_TYPE,
	HEALTH_TYPE,
	DAMAGE_TYPE,
	NUM_PICKUP_TYPES
};

class Pickup :public GameObject
{
public:
	Pickup(Vec3 desiredLoc, PickupType type);
	~Pickup();

	virtual void update();
	virtual void draw();

	Vec3 getLoc() { return mLoc; };
	PickupType getType() { return mType; };
private:
	Vec3 mLoc;
	float mOriginalY;
	PickupType mType;
	Sprite mSprite;
};
#endif
