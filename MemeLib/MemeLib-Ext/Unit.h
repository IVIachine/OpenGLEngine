#ifndef _UNIT_H_
#define _UNIT_H_

#include <GameObject.h>

#include <limits>
#include "Vector3.h"
#include "AStarPathfinder.h"
#include "NavMesh.h"
#include "Component.h"
#include "Sprite.h"
#include "Steering.h"
#include "StateMachine.h"
#include "IdleState.h"
#include "ChaseState.h"
#include "PickupState.h"
#include "UnitManager.h"

class PositionComponent;
class PhysicsComponent;
class SteeringComponent;
class Sprite;
class UnitManager;
class Timer;

const size_t DEFAULT_QUEUE_CAPACITY = 8;

class Unit : public GameObject
{
public:
	virtual bool start();
	virtual void destroy();
	virtual void update();
	virtual void draw();
	virtual void handleEvent(const Event& ev);

	float getFacing() const;

	PositionComponent*	getPositionComponent() const;
	PhysicsComponent*	getPhysicsComponent() const;
	SteeringComponent*	getSteeringComponent() const;

	float getMaxAcc() const { return mMaxAcc; };
	float getMaxSpeed() const { return mMaxSpeed; };
	float getMaxRotAcc() const { return mMaxRotAcc; };
	float getMaxRotVel() const { return mMaxRotVel; };

	void setShowTarget(bool val) { mShowTarget = val; };

	void setSteering(Steering::SteeringType type, Vec3 targetLoc = Vec3(0, 0, 0), GameObjectID targetUnitID = INVALID_GOBJ_ID);

	void findPath(Vec3 source, Vec3 target);
	void findPath(Vec3 target);
	void clear();
	void changeTarg(Vec3 targ) { m_currentTarget = targ; };
	void setPickup(GameObjectID targ) { static_cast<PickupState*>(mpPickupState)->setPickup(targ); };
	Vec3 getTarget() { return m_currentTarget; };
	NavMesh* getNavMesh() { return mp_navMesh; };
	AStarPathfinder* getPathFinder() { return mpPathfinder; };
	void changeSprite(std::string target);
	void applyDamage(float damage);
	void applyBuff(Pickup* pickup);
	static GameObjectID getPlayerID() { return s_playerID; };
	static void setPlayerID(GameObjectID id) { s_playerID = id; };

private:
	//GameObjectID mID;
	ComponentID mPhysicsComponentID;
	ComponentID mPositionComponentID;
	ComponentID mSteeringComponentID;

	Sprite mSprite;
	float mMaxAcc;
	float mMaxSpeed;
	float mMaxRotAcc;
	float mMaxRotVel;
	float mHealth, mDamageRadius, mDamage, mMaxHealth;
	bool mShowTarget;
	bool mPowered;
	NavMesh* mp_navMesh;
	Vec3 m_currentTarget;
	AStarPathfinder* mpPathfinder;
	StateMachine* mpStateMachine;
	StateMachineState* mpIdleState;
	StateMachineState* mpChaseState;
	StateMachineState* mpPickupState;

	StateTransition* mpIdleTransition;
	StateTransition* mpChaseTransition;
	StateTransition* mpPickupTransition;
	Timer* mPowerupTime;
	PickupType mPoweredType;
	void checkNearby();
	Unit(const Sprite& sprite, NavMesh* navMesh, float health, float damageRadius, float damage);
	virtual ~Unit();

	Unit(Unit&);//invalidate copy constructor
	void operator=(Unit&);//invalidate assignment operator

	static GameObjectID s_playerID;

	friend class UnitManager;
};

#endif