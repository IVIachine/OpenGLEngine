#include "IdleState.h"
#include "GameObjectManager.h"
#include "PositionComponent.h"
#include "Unit.h"
#include <map>
#include "Timer.h"
#include "Pickup.h"

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
	//Change to idle sprite
	std::cout << "IDLE\n";
	mpTimeTillSwitch->start();
}

void IdleState::onExit()
{
	mpTimeTillSwitch->stop();
}

StateTransition * IdleState::update(Unit* currentUnit)
{

	 Vec3 playerLoc = static_cast<Unit*>(OBJECT_MANAGER->getData()[PLAYER_ID])->getPositionComponent()->getPosition();
	 Vec3 currentLoc = currentUnit->getPositionComponent()->getPosition();
	 if (glm::distance(playerLoc, currentLoc) < TEMP_DIST)
	 {
		 std::map<TransitionType, StateTransition*>::iterator iter = mTransitions.find(CHASE_TRANSITION);
		 if (iter != mTransitions.end())//found?
		 {
			 StateTransition* pTransition = iter->second;
			 currentUnit->getPathFinder()->setState(AStarState::Idle);
			 return pTransition;
		 }
	 }

	 for (auto obj : OBJECT_MANAGER->getData())
	 {
		 if (Pickup* tmp = static_cast<Pickup*>(obj.second))
		 {
			 if (tmp != NULL)
			 {
				 if (glm::distance(tmp->getLoc(), currentLoc) < TEMP_DIST)
				 {
					 std::map<TransitionType, StateTransition*>::iterator iter = mTransitions.find(PICKUP_TRANSITION);
					 if (iter != mTransitions.end())//found?
					 {
						 currentUnit->setPickup(tmp->getID());
						 StateTransition* pTransition = iter->second;
						 return pTransition;
					 }
				 }
			 }
		 }
	 }

	 if (mpTimeTillSwitch->getElapsedTime() > 10000)
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
