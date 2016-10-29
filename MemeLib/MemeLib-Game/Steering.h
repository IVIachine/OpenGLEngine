#ifndef _STEERING_H_
#define _STEERING_H_

#include "Vector3.h"
#include <Trackable.h>
#include "defines.h"
#include "PhysicsComponent.h"

class Steering : public Trackable
{
public:
	enum SteeringType
	{
		INVALID_TYPE = -1,
		SEEK,
		FLEE,
		ARRIVE,
		WANDER,
		PATH_FOLLOW
	};

	//constructors and destructors
	Steering(SteeringType type = INVALID_TYPE) :mType(type), mTargetLoc(Vec3(0, 0, 0)), mTargetID(INVALID_UNIT_ID), mOwnerID(INVALID_UNIT_ID), mData(ZERO_PHYSICS_DATA) {};
	virtual ~Steering() {};

	//accessors
	void setTargetLoc(const Vec3& loc) { mTargetLoc = loc; };
	const Vec3& getTargetLoc() const { return mTargetLoc; };
	void setTargetID(const UnitID& id) { mTargetID = id; };
	const UnitID& getTargetID() const { return mTargetID; };
	void setOwnerID(const UnitID& id) { mOwnerID = id; };
	//void setData(const PhysicsData& data) { mData = data; };
	const PhysicsData& getData() const { return mData; };
	void setData(PhysicsData theData) { mData = theData; };
	UnitID getOwnerId() const { return mOwnerID; };
	void update();
protected:
	SteeringType mType;
	Vec3 mTargetLoc;
	UnitID mTargetID;
	UnitID mOwnerID;
	PhysicsData mData;

	virtual Steering* getSteering() { return this; };//overridden by sub-classes

};

#endif