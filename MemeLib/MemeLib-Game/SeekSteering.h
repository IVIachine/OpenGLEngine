#ifndef _SEEK_STEERING_H_
#define _SEEK_STEERING_H_

#include <Trackable.h>
#include "Steering.h"

class SeekSteering : public Steering
{
public:
	SeekSteering(
		const UnitID& ownerID, 
		const Vector2& targetLoc, 
		const UnitID& targetID = INVALID_UNIT_ID, 
		bool shouldFlee = false);

	virtual Steering* getSteering();
};

#endif