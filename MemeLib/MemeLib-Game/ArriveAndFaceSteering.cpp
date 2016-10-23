#include "ArriveAndFaceSteering.h"
#include "Steering.h"
#include "Game.h"
#include "UnitManager.h"
#include "Unit.h"


ArriveAndFaceSteering::ArriveAndFaceSteering(
	const UnitID& ownerID,
	const Vector2& targetPos,
	const UnitID& targetID,
	float arriveRadius,
	float arriveSlowRadius,
	float faceSlowRadius,
	float timeToTarget) : Steering(ARRIVE_AND_FACE)
{
	setOwnerID(ownerID);
	setTargetID(targetID);
	setTargetPos(targetPos);

	mp_arrive = new ArriveSteering(
		ownerID, 
		targetPos, 
		targetID, 
		arriveRadius, 
		arriveSlowRadius, 
		timeToTarget);

	mp_face = new FaceSteering(
		ownerID, 
		targetPos, 
		targetID,
		faceSlowRadius);
}

ArriveAndFaceSteering::~ArriveAndFaceSteering()
{
	delete mp_arrive;
	mp_arrive = NULL;

	delete mp_face;
	mp_face = NULL;
}

Steering* ArriveAndFaceSteering::getSteering()
{
	if (mp_face->getSteering() != NULL)
	{
		m_data = mp_face->getSteering()->getData();
	}

	if (mp_arrive->getSteering() != NULL)
	{
		m_data = mp_arrive->getSteering()->getData();
	}

	return this;
}