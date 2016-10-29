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
	mpArriveSteering = new ArriveSteering(ownerID, targetLoc, targetID, .015f, .5, .1);
	mpFaceSteering = new FaceSteering(ownerID, targetLoc, targetID, .005f, 5.0f);
	mSwitchRadius = switchRadius;
	mCurrentIndex = 1;
	mFollowing = false;
}


PathFollowSteering::~PathFollowSteering()
{
	delete mpSeekSteering;
	mpSeekSteering = NULL;

	delete mpArriveSteering;
	mpArriveSteering = NULL;

	delete mpFaceSteering;
	mpFaceSteering = NULL;
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

		diff = mpFollowPath.peek(mCurrentIndex)->getPosition() - pOwner->getPositionComponent()->getPosition();
		if (glm::length(diff) < mSwitchRadius)
		{
			if (mCurrentIndex + 1 != mpFollowPath.size())
			{
				mCurrentIndex++;
			}
		}
		if (mCurrentIndex + 1 == mpFollowPath.size() && glm::length(diff) < .15f)
		{
			mCurrentIndex = 0;
			mpFollowPath.clear();
			mFollowing = false;
			this->mData.acc = Vec3(0, 0, 0);
			this->mData.vel = Vec3(0, 0, 0);
			return this;
		}


		Steering *pTemp;
		mpFaceSteering->setTargetLoc(mpFollowPath.peek(mCurrentIndex)->getPosition());
		pTemp = mpFaceSteering->getSteering();

		if (pTemp != NULL)
		{
			pOwner->getPhysicsComponent()->setData(pTemp->getData());
		}

		if (mCurrentIndex + 1 != mpFollowPath.size())
		{
			mpSeekSteering->setTargetLoc(mpFollowPath.peek(mCurrentIndex)->getPosition());
			pTemp = mpSeekSteering->getSteering();
			if (pTemp != NULL)
			{
				this->mData = pTemp->getData();
			}
			return this;
		}
		else
		{
			mpArriveSteering->setTargetLoc(mpFollowPath.peek(mCurrentIndex)->getPosition());
			pTemp = mpArriveSteering->getSteering();
			if (pTemp != NULL)
			{
				this->mData = pTemp->getData();
			}
			return this;
		}
	}
	return nullptr;
}
