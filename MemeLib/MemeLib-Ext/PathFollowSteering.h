#pragma once
#include "Steering.h"
#include "SeekSteering.h"
#include "ArriveSteering.h"
#include "FaceSteering.h"
#include "Path.h"
class PathFollowSteering : public Steering
{
private:
	SeekSteering* mpSeekSteering;
	ArriveSteering* mpArriveSteering;
	FaceSteering* mpFaceSteering;
	Path mpFollowPath;
	float mSwitchRadius;
	int mCurrentIndex;
	bool mFollowing;

	const float ARRIVE_SLOW = .5f, ARRIVE_RADIUS = .5f, TIME_TO = .1f, FACE_RADIUS = .005f, FACE_SLOW = 5.0f;
public:
	PathFollowSteering(const GameObjectID& ownerID, const Vec3& targetLoc, const GameObjectID& targetID, float switchRadius);
	~PathFollowSteering();

	virtual Steering* getSteering();
	void setPath(Path path) { mpFollowPath = path; mFollowing = true; };
};

