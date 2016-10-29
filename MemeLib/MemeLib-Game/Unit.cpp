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

	if (AStarPathfinder* pAstar = static_cast<AStarPathfinder*>(mpPathfinder))
	{
		AStarOptions* pOpt = pAstar->getOptions();
		pOpt->enableDiagonals = true;
		pOpt->enableHeuristic = true;
		pOpt->maxDistance = 0;
	}

	mpPathfinder->findPath(graph->getNode(0), graph->getNode(5));
	mExpectingPath = true;
}


Unit::~Unit()
{
	delete mpPathfinder;
	mpPathfinder = NULL;
}

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

void Unit::update(float elapsedTime)
{
	if (mExpectingPath && mpPathfinder->getPath().size() > 0)
	{
		getSteeringComponent()->setData(getSteeringComponent()->getData(), mpPathfinder->getPath());
		mExpectingPath = false;
	}
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

