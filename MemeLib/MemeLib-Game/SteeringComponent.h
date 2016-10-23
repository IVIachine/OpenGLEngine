#ifndef _STEERING_COMPONENT_H_
#define _STEERING_COMPONENT_H_

#include <Trackable.h>
#include "Component.h"
#include "Unit.h"
#include "Vector2.h"

class PhysicsComponent;
class Steering;
enum Steering::SteeringType;

struct SteeringData : public Trackable
{
	SteeringData() :type(
		Steering::INVALID_TYPE),
		targetPos(Vector2::ZERO),
		ownerID(INVALID_UNIT_ID),
		targetID(INVALID_UNIT_ID)
	{};

	SteeringData(
		Steering::SteeringType theType,
		const Vector2& theTargetLoc = Vector2::ZERO,
		UnitID theOwner = INVALID_UNIT_ID,
		UnitID theTarget = INVALID_UNIT_ID)
		:type(theType),
		targetPos(theTargetLoc),
		ownerID(theOwner),
		targetID(theTarget)
	{};

	Steering::SteeringType type;
	Vector2 targetPos;
	UnitID ownerID;
	UnitID targetID;
};

const SteeringData ZERO_STEERING_DATA;

class SteeringComponent :public Component
{
public:
	//getters and setters
	Steering::SteeringType	getType() const { return m_steeringData.type; };
	const Vector2&			getTargetLoc() const { return m_steeringData.targetPos; };
	UnitID					getOwnerID() const { return m_steeringData.ownerID; };
	UnitID					getTargetID() const { return m_steeringData.targetID; };
	ComponentID				getPhysicsID() const { return m_physicsID; };
	const SteeringData&		getData() const { return m_steeringData; };

	void	setData(const SteeringData& data);
	void	setSteering(Steering* steering);
	void	setTargetPos(const Vector2& position) { m_steeringData.targetPos = position; };
	void	setTargetUnitID(const UnitID& id) { m_steeringData.targetID = id; };
	void	applySteering(PhysicsComponent& physicsComponent);

	inline Steering* getSteering() const
	{
		return mp_steering;
	}

private:
	ComponentID m_physicsID;
	SteeringData m_steeringData;
	Steering* mp_steering;

	SteeringComponent(const ComponentID& id, const ComponentID& physicsComponentID);
	~SteeringComponent();

	friend class ComponentManager;

	friend class Message_UpdateFlocking;  // spaghetti code
};

#endif