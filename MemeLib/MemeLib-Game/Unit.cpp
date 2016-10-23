#include "Unit.h"
#include <fstream>
#include <assert.h>

#include "Game.h"
#include "Graphics.h"
#include "Component.h"
#include "TransformCOmponent.h"
#include "PhysicsComponent.h"
#include "SteeringComponent.h"
#include "ComponentManager.h"
//#include "SpriteManager.h"
//#include "Gizmos.h"

const bool SHOW_UNIT_DIRECTIONS = false;

Unit::Unit(const Sprite& sprite)
	: mSprite(sprite)
	, mTransformComponentID(INVALID_COMPONENT_ID)
	, mPhysicsComponentID(INVALID_COMPONENT_ID)
	, mSteeringComponentID(INVALID_COMPONENT_ID)
	, mShowTarget(false)
{
}

Unit::~Unit()
{
}


void Unit::update(float elapsedTime)
{
	Vector2 pos = getTransformComponent()->getPosition();
	//GRAPHICS->wrapCoordinates(pos);
	getTransformComponent()->setPosition(pos);

	m_position = getTransformComponent()->getPosition();
	m_rotation = getTransformComponent()->getRotation();
}

void Unit::draw() const
{
	TransformComponent* pTransform = getTransformComponent();
	assert(pTransform != NULL);
	Vector2 position = pTransform->getPosition();
	
	//GRAPHICS->drawSprite(mSprite, position);

	if (mShowTarget)
	{
		SteeringComponent* pSteering = getSteeringComponent();
		assert(pSteering != NULL);
		const Vector2& targetLoc = pSteering->getTargetLoc();
		if (&targetLoc != &Vector2::ZERO)
		{
			//GIZMOS->drawCircle(targetLoc, 5, Color::RED, 1);
		}
	}

	

	if (SHOW_UNIT_DIRECTIONS)
	{
		// Forward
		//GIZMOS->drawLine(position, position + pTransform->forward() * 50.f, Color::YELLOW, 1.f);
		// Backward
		//GIZMOS->drawLine(position, position + pTransform->backward() * 50.f, Color::RED, 1.f);
		// Left
		//GIZMOS->drawLine(position, position + pTransform->left() * 50.f, Color::BLUE, 1.f);
		// Right
		//GIZMOS->drawLine(position, position + pTransform->right() * 50.f, Color::GREEN, 1.f);
	}
}


TransformComponent* Unit::getTransformComponent() const
{
	TransformComponent* pComponent = COMPONENTS->getTransformComponent(mTransformComponentID);
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


void Unit::setSteering(Steering::SteeringType type, Vector2 targetLoc, UnitID targetUnitID)
{
	SteeringComponent* pSteeringComponent = getSteeringComponent();
	if (pSteeringComponent != NULL)
	{
		pSteeringComponent->setData(SteeringData(type, targetLoc, mID, targetUnitID));
	}
}

/*
void Unit::postTransaction(const Transaction& transaction)
{
	switch(transaction.type)
	{
	case POSITION_TRANSACTION:
	{
	bool posted = mPositionTransactionQueue.pushBack(static_cast<const PositionTransaction&>(transaction));
	assert(posted);
	break;
	}
	default:
	break;
	}
}

void Unit::processTransactions()
{
PositionTransaction trans;
while (mPositionTransactionQueue.popFront(trans))
{

}
}
*/


Vector2 Unit::getPosition() const
{
	return m_position;
}

float Unit::getRotation() const
{
	return m_rotation;
}