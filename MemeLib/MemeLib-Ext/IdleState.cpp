#include "IdleState.h"
#include "GameObjectManager.h"
#include "PositionComponent.h"
#include "Unit.h"
#include <map>
#include "Timer.h"
#include "Pickup.h"
#include "UnitManager.h"

IdleState::IdleState(const SM_idType & id)
	:StateMachineState(id)
{
	mpTimeTillSwitch = new Timer();
}
IdleState::~IdleState()
{
	delete mpTimeTillSwitch;
	mpTimeTillSwitch = NULL;
}
void IdleState::onEntrance()
{
	mSpriteChange = true;
	mpTimeTillSwitch->start();
}

void IdleState::onExit()
{
	mpTimeTillSwitch->stop();
}

StateTransition * IdleState::update(Unit* currentUnit)
{
	if (mSpriteChange)
	{
		currentUnit->changeSprite("idle");
		mSpriteChange = false;
	}

	Unit* pPlayer = UNITS->getUnit(Unit::getPlayerID());
	if (!pPlayer)
	{
		std::cout << toString() << " PLAYER IS NULL\n";
		return NULL;
	}

	//Vec3 playerLoc = static_cast<Unit*>(OBJECT_MANAGER->getData()[s_playerID])->getPositionComponent()->getPosition();
	Vec3 playerLoc = pPlayer->getPositionComponent()->getPosition();
	Vec3 currentLoc = currentUnit->getPositionComponent()->getPosition();
	if (glm::distance(playerLoc, currentLoc) < TEMP_DIST_CHASE)
	{
		std::map<TransitionType, StateTransition*>::iterator iter = mTransitions.find(CHASE_TRANSITION);
		if (iter != mTransitions.end())//found?
		{
			StateTransition* pTransition = iter->second;
			currentUnit->getPathFinder()->setState(AStarState::Idle);
			return pTransition;
		}
	}

	std::vector<Pickup*> pickups = OBJECT_MANAGER->findObjectsOfType<Pickup>();
	if (pickups.size() > 0)
	{
		for (auto pickup : pickups)
		{
			if (pickup!= NULL)
			{
				if (glm::distance(pickup->getLoc(), currentLoc) < TEMP_DIST_PICK)
				{
					std::map<TransitionType, StateTransition*>::iterator iter = mTransitions.find(PICKUP_TRANSITION);
					if (iter != mTransitions.end())//found?
					{
						GameObjectID id = pickup->getID();
						currentUnit->setPickup(id);
						StateTransition* pTransition = iter->second;
						return pTransition;
					}
				}
			}
		}
	}

	if (mpTimeTillSwitch->getElapsedTime() > 5000)
	{
		mpTimeTillSwitch->stop();
		int randIndex = rand() % (currentUnit->getNavMesh()->getVerts().size() - 1);
		currentUnit->findPath(currentUnit->getNavMesh()->getVerts()[randIndex]);
		mpTimeTillSwitch->start();
	}
	//Check dist from all powerups



	//If distances are a below the threshhold, change states
	return NULL;
}
