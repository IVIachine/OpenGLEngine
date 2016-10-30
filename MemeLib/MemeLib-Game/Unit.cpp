#include "Unit.h"
#include <assert.h>
#include "GameApp.h"
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

Unit::Unit(const Sprite& sprite, NavMesh* navMesh)
	:mSprite(sprite)
	,mPositionComponentID(INVALID_COMPONENT_ID)
	,mPhysicsComponentID(INVALID_COMPONENT_ID)
	,mSteeringComponentID(INVALID_COMPONENT_ID)
	,mShowTarget(false)
{
	mp_navMesh = navMesh;

	mpPathfinder = new AStarPathfinder(mp_navMesh);

	AStarOptions* pOpt = mpPathfinder->getOptions();
	pOpt->enableDiagonals = true;
	pOpt->enableHeuristic = true;
	pOpt->maxDistance = 0;
	mp_currentTarget = Vec3(0, 0, 0);
	EVENT_SYSTEM->addListener(PATH_EVENT, this);
	EVENT_SYSTEM->addListener(TARGET_EVENT, this);
}

Unit::~Unit()
{
	cleanup();
}


void Unit::update(float elapsedTime)
{
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

			getSteeringComponent()->setData(data, path);
		}
		else
		{
			std::cout << "No path found.\n";
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

void Unit::setSteering(Steering::SteeringType type, Vec3 targetLoc /*= ZERO_VECTOR2D*/, UnitID targetUnitID /*= INVALID_UNIT_ID*/)
{
	SteeringComponent* pSteeringComponent = getSteeringComponent();
	if (pSteeringComponent != NULL)
	{
		pSteeringComponent->setData(SteeringData(type, targetLoc, mID, targetUnitID));
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

void Unit::cleanup()
{
	delete mpPathfinder;
	mpPathfinder = NULL;
}

float Unit::getFacing() const
{
	PositionComponent* pPosition = getPositionComponent();
	assert(pPosition != NULL);
	return pPosition->getFacing();
}

void Unit::handleEvent(const Event & ev)
{
	if (ev.getType() == PATH_EVENT)
	{
		findPath(mp_currentTarget);
	}
	else if (ev.getType() == TARGET_EVENT)
	{
		const ChangeTargetEvent& changeEvent = static_cast<const ChangeTargetEvent&>(ev);
		mp_currentTarget = changeEvent.getTarg();
	}
}
