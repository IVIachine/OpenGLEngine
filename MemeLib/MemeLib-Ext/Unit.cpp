#include "Unit.h"
#include <assert.h>
#include "Game.h"
#include "Graphics.h"
#include "Component.h"
#include "PositionComponent.h"
#include "PhysicsComponent.h"
#include "SteeringComponent.h"
#include "ResourceManager.h"
#include "AStarPathfinder.h"
#include "EventSystem.h"
#include "BeginPathingEvent.h"
#include "ChangeTargetEvent.h"
#include "ComponentManager.h"
#include "GameobjectManager.h"
#include "Timer.h"

GameObjectID Unit::s_playerID = INVALID_GOBJ_ID;

bool getTestIntersection(Edge edge, Vec3 ip)
{
	Vec3 a = edge.first;
	Vec3 b = edge.second;
	Vec3 c = ip;

	float dac = Vector3::distance(a, c);
	float dbc = Vector3::distance(b, c);
	float dab = Vector3::distance(a, b);
	float sum = dac + dbc;

	if (sum == dab)
	{
		return true;
	}
	else if (sum >= dab - .05f && sum < dab + .05f)
	{
		return true;
	}

	return false;
}

Unit::Unit(const Sprite& sprite, NavMesh* navMesh, float health, float damageRadius, float damage)
	:mSprite(sprite)
	,mPositionComponentID(INVALID_COMPONENT_ID)
	,mPhysicsComponentID(INVALID_COMPONENT_ID)
	,mSteeringComponentID(INVALID_COMPONENT_ID)
	,mShowTarget(false)
	,mHealth(health)
	,mDamageRadius(damageRadius)
	,mDamage(damage)
{
	mMaxHealth = health;
	mp_navMesh = navMesh;

	mpPathfinder = new AStarPathfinder(mp_navMesh);

	AStarOptions* pOpt = mpPathfinder->getOptions();
	pOpt->enableDiagonals = true;
	pOpt->enableHeuristic = true;
	pOpt->maxDistance = 0;
	m_currentTarget = Vec3(0, 0, 0);

	if (getID() != s_playerID)
	{
		mpStateMachine = new StateMachine();

		mpIdleState = new IdleState(0);
		mpChaseState = new ChaseState(1);
		mpPickupState = new PickupState(2);

		mpIdleTransition = new StateTransition(IDLE_TRANSITION, 0);
		mpChaseTransition = new StateTransition(CHASE_TRANSITION, 1);
		mpPickupTransition = new StateTransition(PICKUP_TRANSITION, 2);

		mpIdleState->addTransition(mpChaseTransition);
		mpIdleState->addTransition(mpPickupTransition);

		mpChaseState->addTransition(mpIdleTransition);
		mpPickupState->addTransition(mpIdleTransition);
		mpPickupState->addTransition(mpChaseTransition);

		mpStateMachine->addState(mpIdleState);
		mpStateMachine->addState(mpChaseState);
		mpStateMachine->addState(mpPickupState);
		mpStateMachine->setInitialStateID(0);
	}
	else
	{
		//Create Player states
	}
	mPowerupTime = new Timer();
	mPowered = false;
	mPoweredType = PickupType::INVALID_PICKUP_TYPE;
}

Unit::~Unit()
{
	clear();
}


bool Unit::start()
{
	return false;
}

void Unit::destroy()
{
}

void Unit::update()
{
	checkNearby();

	if (getID() != s_playerID)
	{
		mpStateMachine->update(this);
	}

	if (mPowered == true && mPowerupTime->getElapsedTime() > 10000)
	{
		mPowerupTime->stop();
		mPowered = false;

		if (mPoweredType == PickupType::SPEED_TYPE)
		{
			PhysicsData tmp = getPhysicsComponent()->getData();
			tmp.maxSpeed -= .2f;
			getPhysicsComponent()->setData(tmp);
			mPoweredType = PickupType::INVALID_PICKUP_TYPE;
		}
		else if (mPoweredType == PickupType::DAMAGE_TYPE)
		{
			mDamage -= .03f;
			mPoweredType = PickupType::INVALID_PICKUP_TYPE;
		}
	}

	AStarState pathState = mpPathfinder->getState();
	switch (pathState)
	{
	case Idle:
	{
		//findPath(mp_navMesh->getNode(5)->getPosition());
	}
	break;
	case Working:
	{
		mpPathfinder->step();
	}
	break;
	case Done:
	{
		if (mpPathfinder->endStep() == PathFound)
		{
			SteeringData data = getSteeringComponent()->getData();
			Path path = mpPathfinder->getPath();
			Vec3 pos = getPositionComponent()->getPosition();
			//remove nodes that backtrack AI (Doesn't fully work)
			for (size_t i = 1; i < path.size(); i++)
			{
				if (getTestIntersection(Edge(path.peek(0)->getPosition(), path.peek(i)->getPosition()), pos))
				{
					path.removeFront();
					i = 1;
				}
			}

			getSteeringComponent()->setData(data, path);
		}
		else
		{
			//std::cout << "No path found.\n";
		}
	}
	break;
	default:
		break;
	}
}

void Unit::draw()
{
	PositionComponent* pTransform = getPositionComponent();
	mSprite.setPosition(pTransform->getPosition());
	mSprite.setYRotation(pTransform->getFacing());
	mSprite.draw(*GRAPHICS->getCamera());
}

void Unit::handleEvent(const Event & ev)
{
}


PositionComponent* Unit::getPositionComponent() const
{
	PositionComponent* pComponent = COMPONENTS->getPositionComponent(mPositionComponentID);
	return pComponent;
}

PhysicsComponent* Unit::getPhysicsComponent() const
{
	PhysicsComponent* pComponent = COMPONENTS->getPhysicsComponent(mPhysicsComponentID);
	return pComponent;
}

SteeringComponent* Unit::getSteeringComponent() const
{
	SteeringComponent* pComponent = COMPONENTS->getSteeringComponent(mSteeringComponentID);
	return pComponent;
}


void Unit::setSteering(Steering::SteeringType type, Vec3 targetLoc, GameObjectID targetUnitID)
{
	SteeringComponent* pSteeringComponent = getSteeringComponent();
	if (pSteeringComponent != NULL)
	{
		pSteeringComponent->setData(SteeringData(type, targetLoc, getID(), targetUnitID));
	}
}

void Unit::findPath(Vec3 source, Vec3 target)
{
	mpPathfinder->setSource(mp_navMesh->findNearestNode(source));
	mpPathfinder->setTarget(mp_navMesh->findNearestNode(target));
	mpPathfinder->beginStep();
}

void Unit::findPath(Vec3 target)
{
	findPath(getPositionComponent()->getPosition(), target);
}

void Unit::checkNearby()
{
	if (getID() != s_playerID)
	{
		Unit* player = OBJECT_MANAGER->findByID<Unit>(s_playerID);
		if (glm::distance(player->getPositionComponent()->getPosition(), getPositionComponent()->getPosition()) < mDamageRadius)
		{
			player->applyDamage(mDamage);
		}
	}
	else
	{
		std::vector<Unit*> enemies = OBJECT_MANAGER->findObjectsOfType<Unit>();
		Vec3 pos = getPositionComponent()->getPosition();
		for (auto enemy : enemies)
		{
			if (enemy->getID() != s_playerID)
			{
				if (glm::distance(enemy->getPositionComponent()->getPosition(), pos) < mDamageRadius)
				{
					enemy->applyDamage(mDamage);
				}
			}
		}
	}
}

void Unit::clear()
{
	delete mpPathfinder;
	mpPathfinder = NULL;

	delete mpStateMachine;
	mpStateMachine = NULL;

	delete mpIdleState;
	mpIdleState = NULL;

	delete mpChaseState;
	mpChaseState = NULL;

	delete mpIdleTransition;
	mpIdleTransition = NULL;

	delete mpChaseTransition;
	mpChaseTransition = NULL;

	delete mpPickupState;
	mpPickupState = NULL;

	delete mpPickupTransition;
	mpPickupTransition = NULL;

	delete mPowerupTime;
	mPowerupTime = NULL;
}

void Unit::changeSprite(std::string target)
{
	if (RESOURCES->getSprite(target) != NULL)
	{
		mSprite = *RESOURCES->getSprite(target);
	}
	else
	{
		std::cout << "Desired Sprite NULL\n";
	}
}

void Unit::applyDamage(float damage)
{
	mHealth -= damage;
	if (mHealth < 1)
	{
		if (getID() != s_playerID)
		{
			UNITS->deleteUnit(getID());
		}
		else
		{
			std::cout << "PLAYER_DEAD\n";
		}
	}

	if (getID() == s_playerID)
	{
		GRAPHICS->setWindowTitle("Health: " + std::to_string(mHealth));
	}
}

void Unit::applyBuff(Pickup * pickup)
{
	if (mPowered == true)
	{
		mPowerupTime->stop();
		if (mPoweredType == PickupType::SPEED_TYPE)
		{
			PhysicsData tmp = getPhysicsComponent()->getData();
			tmp.maxSpeed -= .2f;
			getPhysicsComponent()->setData(tmp);
			mPowered = false;
			mPoweredType = PickupType::INVALID_PICKUP_TYPE;
		}
		else if (mPoweredType == PickupType::DAMAGE_TYPE)
		{
			mDamage -= .03f;
			mPowered = false;
			mPoweredType = PickupType::INVALID_PICKUP_TYPE;
		}
	}

	if (pickup->getType() == PickupType::SPEED_TYPE)
	{
		PhysicsData tmp = getPhysicsComponent()->getData();
		tmp.maxSpeed += .2f;
		getPhysicsComponent()->setData(tmp);
		mPoweredType = PickupType::SPEED_TYPE;
		mPowerupTime->start();
		mPowered = true;
	}
	else if (pickup->getType() == PickupType::DAMAGE_TYPE)
	{
		mDamage += .03f;
		mPoweredType = PickupType::DAMAGE_TYPE;
		mPowerupTime->start();
		mPowered = true;
	}
	else if (pickup->getType() == PickupType::HEALTH_TYPE)
	{
		mHealth += 50;
		if (mHealth > mMaxHealth)
		{
			mHealth = mMaxHealth;
		}
	}
}

float Unit::getFacing() const
{
	PositionComponent* pPosition = getPositionComponent();
	assert(pPosition != NULL);
	return pPosition->getFacing();
}


