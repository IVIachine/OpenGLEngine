#include "PathFollowSteering.h"
#include "UnitManager.h"
#include "Node.h"

PathFollowSteering::PathFollowSteering(const UnitID& ownerID, const Vec3& targetLoc, const UnitID& targetID, float switchRadius)
:Steering()
{
	setOwnerID(ownerID);
	setTargetID(targetID);
	setTargetLoc(targetLoc);

	mpSeekSteering = new SeekSteering(ownerID, targetLoc, targetID, false);
	mSwitchRadius = switchRadius;
	mCurrentIndex = 1;
	mFollowing = false;
}


PathFollowSteering::~PathFollowSteering()
{
	delete mpSeekSteering;
	mpSeekSteering = NULL;
}

Steering* PathFollowSteering::getSteering()
{
	if (mFollowing)
	{
		if (mpFollowPath.size() <= 0)
		{
			mFollowing = false;
			return nullptr;
		}

		Vec3 diff;
		Unit* pOwner = UNITS->getUnit(mOwnerID);

		bool checkForSwitch = true;
		while (checkForSwitch) //Loop until there is a target far enough a way to travel to
		{
			diff = mpFollowPath.peek(mCurrentIndex)->getPosition() - pOwner->getPositionComponent()->getPosition();
			if (glm::length(diff) < mSwitchRadius)
			{ 
				if (mCurrentIndex + 1 != mpFollowPath.size())
				{
					mCurrentIndex++;
				}
				else
				{
					mCurrentIndex = 0;
					mpFollowPath.clear();
					mFollowing = false;
					return nullptr;
				}
			}
			else
				checkForSwitch = false;
		}

		mpSeekSteering->setTargetLoc(mpFollowPath.peek(mCurrentIndex)->getPosition());
		Steering *pTemp = mpSeekSteering->getSteering();
		if (pTemp != NULL)
		{
			this->mData = pTemp->getData();
			std::cout << mData.vel.x << " " << mData.vel.y << " " << mData.vel.z << std::endl;
		}
		return this;
	}
	return nullptr;
}
