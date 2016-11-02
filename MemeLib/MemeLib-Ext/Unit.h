#ifndef _UNIT_H_
#define _UNIT_H_

#include <Trackable.h>
#include <limits>
#include "Vector3.h"
#include "AStarPathfinder.h"
#include "NavMesh.h"
#include "Component.h"
#include "Sprite.h"
#include "Steering.h"

class PositionComponent;
class PhysicsComponent;
class SteeringComponent;
class Sprite;
class UnitManager;

typedef Uint32 UnitID;
const Uint32 DEFAULT_QUEUE_CAPACITY = 8;

class Unit
{
public:
	void draw();

	float getFacing() const;
	void update(float elapsedTime);

	PositionComponent*	getPositionComponent() const;
	PhysicsComponent*	getPhysicsComponent() const;
	SteeringComponent*	getSteeringComponent() const;

	float getMaxAcc() const { return mMaxAcc; };
	float getMaxSpeed() const { return mMaxSpeed; };
	float getMaxRotAcc() const { return mMaxRotAcc; };
	float getMaxRotVel() const { return mMaxRotVel; };

	void setShowTarget(bool val) { mShowTarget = val; };

	void setSteering(Steering::SteeringType type, Vec3 targetLoc = Vec3(0, 0, 0), UnitID targetUnitID = INVALID_UNIT_ID);

	void findPath(Vec3 source, Vec3 target);
	void findPath(Vec3 target);
	void cleanup();
	void changeTarg(Vec3 targ) { m_currentTarget = targ; };
	Vec3 getTarget() { return m_currentTarget; };

private:
	UnitID mID;
	ComponentID mPhysicsComponentID;
	ComponentID mPositionComponentID;
	ComponentID mSteeringComponentID;

	Sprite mSprite;
	float mMaxAcc;
	float mMaxSpeed;
	float mMaxRotAcc;
	float mMaxRotVel;
	bool mShowTarget;

	NavMesh* mp_navMesh;
	Vec3 m_currentTarget;
	AStarPathfinder* mpPathfinder;
	Unit(const Sprite& sprite, NavMesh* navMesh);
	virtual ~Unit();

	Unit(Unit&);//invalidate copy constructor
	void operator=(Unit&);//invalidate assignment operator


	friend class UnitManager;
};

#endif