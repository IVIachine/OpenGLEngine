#ifndef _ARRIVE_AND_FACE_STEERING_H_
#define _ARRIVE_AND_FACE_STEERING_H_

#include <Trackable.h>
#include "Steering.h"
#include "ArriveSteering.h"
#include "FaceSteering.h"

class ArriveAndFaceSteering : public Steering
{
public:
	ArriveAndFaceSteering(
		const UnitID& ownerID,
		const Vector2& targetPos,
		const UnitID& targetID = INVALID_UNIT_ID,
		float arriveRadius = 32.0f,
		float arriveSlowRadius = 150.0f,
		float faceSlowRadius = 50.0f,
		float timeToTarget = 0.1f);

	~ArriveAndFaceSteering();

	virtual Steering* getSteering();

	void setTargetPos(const Vector2& pos)
	{
		Steering::setTargetPos(pos);
		mp_arrive->setTargetPos(pos);
		mp_face->setTargetPos(pos);
	}

	void modVel(Vector2 amt)
	{
		m_data.vel += amt;
	}

private:
	ArriveSteering* mp_arrive;
	FaceSteering* mp_face;
};


#endif