#ifndef _SEEK_STEERING_H_
#define _SEEK_STEERING_H_

#include <Trackable.h>
#include "Steering.h"

class SeekSteering : public Steering
{
public:
	SeekSteering(const GameObjectID& ownerID, const Vec3& targetLoc, const GameObjectID& targetID = INVALID_GOBJ_ID, bool shouldFlee = false);
	virtual Steering* getSteering();
};

#endif