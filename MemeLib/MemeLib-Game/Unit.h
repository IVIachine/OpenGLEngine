#ifndef _UNIT_H_
#define _UNIT_H_

#include <Trackable.h>
#include <DeanLibDefines.h>
#include <limits>
#include "Vector3.h"
#include "AStarPathfinder.h"
#include "NavMesh.h"
#include "Component.h"
#include "Sprite.h"
#include "Steering.h"
#include "Event.h"
#include "EventListener.h"

class PositionComponent;
class PhysicsComponent;
class SteeringComponent;
class Sprite;
class UnitManager;

const Uint32 DEFAULT_QUEUE_CAPACITY = 8;

//class Unit : public TransactionProcessor
class Unit : public EventListener
{
public:
	//void postTransaction(const Transaction& transaction);
	//void processTransactions();
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
	virtual void handleEvent(const Event& ev);
private:
	UnitID mID;
	ComponentID mPhysicsComponentID;
	ComponentID mPositionComponentID;
	ComponentID mSteeringComponentID;
	//CircularQueue<PositionTransaction, DEFAULT_QUEUE_CAPACITY> mPositionTransactionQueue;
	Sprite mSprite;
	float mMaxAcc;
	float mMaxSpeed;
	float mMaxRotAcc;
	float mMaxRotVel;
	bool mShowTarget;

	NavMesh* mp_navMesh;
	Vec3 mp_currentTarget;
	AStarPathfinder* mpPathfinder;
	Unit(const Sprite& sprite, NavMesh* navMesh);
	virtual ~Unit();

	Unit(Unit&);//invalidate copy constructor
	void operator=(Unit&);//invalidate assignment operator


	friend class UnitManager;
};

#endif