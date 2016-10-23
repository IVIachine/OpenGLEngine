#ifndef _STEERING_H_
#define _STEERING_H_

/*Steering - implementation of Steering class from "Artificial Intelligence for Games" - Millington and Funge
*/

#include <Trackable.h>
#include "defines.h"
#include "PhysicsComponent.h"
#include "Vector2.h"

class Unit;

class Steering : public Trackable
{
public:

	enum SteeringType
	{
		INVALID_TYPE = -1,
		SEEK, FLEE,
		ARRIVE, FACE, ARRIVE_AND_FACE,
		WANDER, WANDER_AND_CHASE,
		ALIGNMENT, COHESION, SEPARATION, FLOCK
	};

	//constructors and destructors
	Steering(SteeringType type = INVALID_TYPE) :
		m_type(type),
		m_targetPos(Vector2::ZERO),
		m_targetID(INVALID_UNIT_ID),
		m_ownerID(INVALID_UNIT_ID),
		m_data(ZERO_PHYSICS_DATA) {};

	virtual ~Steering() {};

	//accessors
	virtual void setTargetPos(const Vector2& loc) { m_targetPos = loc; };
	const	Vector2& getTargetLoc() const { return m_targetPos; };

	void	setTargetID(const UnitID& id) { m_targetID = id; };
	const	UnitID& getTargetID() const { return m_targetID; };

	void	setOwnerID(const UnitID& id) { m_ownerID = id; };
	void	setData(const PhysicsData& data) { m_data = data; };
	const	PhysicsData& getData() const { return m_data; };

	void	update();

	virtual Steering* getSteering() { return this; }; // overridden by sub-classes


protected:
	friend class Steering;

	SteeringType	m_type;
	Vector2			m_targetPos;
	UnitID			m_targetID;
	UnitID			m_ownerID;
	PhysicsData		m_data;

};

#endif