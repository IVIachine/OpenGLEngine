#pragma once
#include "Steering.h"
#include "SeekSteering.h"
#include "ArriveSteering.h"
#include "FaceSteering.h"
#include "Path.h"
class PathFollowSteering: public Steering
{
private:
	SeekSteering* mpSeekSteering;
	ArriveSteering* mpArriveSteering;
	FaceSteering* mpFaceSteering;
	Path mpFollowPath;
	float mSwitchRadius;
	int mCurrentIndex;
	bool mFollowing;
public:
	PathFollowSteering(const UnitID& ownerID, const Vec3& targetLoc, const UnitID& targetID, float switchRadius);
	~PathFollowSteering();

	virtual Steering* getSteering();
	void setPath(Path path) { mpFollowPath = path; mFollowing = true; };
};

