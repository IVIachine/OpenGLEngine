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

Unit::Unit(const Sprite& sprite, NavMesh* graph)
	:mSprite(sprite)
	,mPositionComponentID(INVALID_COMPONENT_ID)
	,mPhysicsComponentID(INVALID_COMPONENT_ID)
	,mSteeringComponentID(INVALID_COMPONENT_ID)
	,mShowTarget(false)
{
	mpPathfinder = new AStarPathfinder(graph);
	AStarOptions* pOpt = mpPathfinder->getOptions();

<<<<<<< HEAD
	pOpt->enableDiagonals = false;
	pOpt->enableHeuristic = true;
	pOpt->maxDistance = 0;
=======
	if (AStarPathfinder* pAstar = static_cast<AStarPathfinder*>(mpPathfinder))
	{
		AStarOptions* pOpt = pAstar->getOptions();
		pOpt->enableDiagonals = true;
		pOpt->enableHeuristic = true;
		pOpt->maxDistance = 0;
	}
>>>>>>> 4a5592d5a831d5336f3a6fa74d039cca880907fb

	mpPathfinder->setSource(graph->getNode(0));
	mpPathfinder->setTarget(graph->getNode(5));
	mpPathfinder->beginStep();
}

Unit::~Unit()
{
	delete mpPathfinder;
	mpPathfinder = NULL;
}

<<<<<<< HEAD
=======
void Unit::draw() 
{
	PositionComponent* pTransform = getPositionComponent();
	mSprite.setPosition(pTransform->getPosition());
	mSprite.setYRotation(pTransform->getFacing());
	mSprite.draw(*GRAPHICS->getCamera());
}

float Unit::getFacing() const
{
	PositionComponent* pPosition = getPositionComponent();
	assert(pPosition != NULL);
	return pPosition->getFacing();
}
>>>>>>> 4a5592d5a831d5336f3a6fa74d039cca880907fb

void Unit::update(float elapsedTime)
{
	AStarState state = mpPathfinder->getState();

	if (state == Working)
	{
		mpPathfinder->step();
	}
	else if (state == Done)
	{
		if (mpPathfinder->endStep() == PathFound)
		{
			getSteeringComponent()->setData(getSteeringComponent()->getData(), mpPathfinder->getPath());
		}
		else
		{
			std::cout << "No path found.\n";
		}
	}
}

void Unit::draw()
{
	PositionComponent* pTransform = getPositionComponent();
	mSprite.setPosition(pTransform->getPosition());
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

float Unit::getFacing() const
{
	PositionComponent* pPosition = getPositionComponent();
	assert(pPosition != NULL);
	return pPosition->getFacing();
}