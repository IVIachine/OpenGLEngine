#ifndef _UNIT_H_
#define _UNIT_H_

#include <Trackable.h>
#include <DeanLibDefines.h>
#include <limits>

#include "Component.h"
#include "Steering.h"
#include "Vector2.h"
#include "Sprite.h"
//#include "CircularQueue.h"
//#include "Transaction.h"
//#include "TransactionProcessor.h"

class TransformComponent;
class PhysicsComponent;
class SteeringComponent;
class UnitManager;
const Uint32 DEFAULT_QUEUE_CAPACITY = 8;

//class Unit : public TransactionProcessor
class Unit : public Trackable
{
public:
	//void postTransaction(const Transaction& transaction);
	//void processTransactions();
	void	update(float elapsedTime);
	void	draw() const;

	TransformComponent*	getTransformComponent() const;
	PhysicsComponent*	getPhysicsComponent() const;
	SteeringComponent*	getSteeringComponent() const;

	float	getMaxAcc() const { return mMaxAcc; };
	float	getMaxSpeed() const { return mMaxSpeed; };
	float	getMaxRotAcc() const { return mMaxRotAcc; };
	float	getMaxRotVel() const { return mMaxRotVel; };

	void	setShowTarget(bool val) { mShowTarget = val; };
	void	setSteering(Steering::SteeringType type, Vector2 targetLoc = Vector2::ZERO, UnitID targetUnitID = INVALID_UNIT_ID);

	Vector2 getPosition() const;
	float	getRotation() const;

private:
	UnitID mID;
	ComponentID mPhysicsComponentID;
	ComponentID mTransformComponentID;
	ComponentID mSteeringComponentID;
	//CircularQueue<PositionTransaction, DEFAULT_QUEUE_CAPACITY> mPositionTransactionQueue;
	Sprite mSprite;

	float mMaxAcc;
	float mMaxSpeed;
	float mMaxRotAcc;
	float mMaxRotVel;
	bool mShowTarget;

	Vector2 m_position;
	float m_rotation;

	Unit(const Sprite& sprite);
	virtual ~Unit();

	Unit(Unit&);//invalidate copy constructor
	void operator=(Unit&);//invalidate assignment operator


	friend class UnitManager;
};

#endif