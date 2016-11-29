#ifndef PICKUP_H
#define PICKUP_H

#include "GameObject.h"
#include "Vector3.h"
#include <Sprite.h>

class Sprite;

enum PickupType
{
	INVALID_TYPE = -1,
	SPEED_TYPE,
	DETECTION_RANGE_TYPE
};

class Pickup :public GameObject
{
public:
	Pickup(Vec3 desiredLoc, PickupType type);
	~Pickup();

	virtual void update();
	virtual void draw();

	Vec3 getLoc() { return mLoc; };

private:
	Vec3 mLoc;
	PickupType mType;
	Sprite mSprite;
};
#endif
