#ifndef _PHYSICS_COMPONENT_H_
#define _PHYSICS_COMPONENT_H_

#include "Component.h"
#include <Trackable.h>
#include <cfloat>
#include "Vector2.h"

class TransformComponent;

static const float PHYS_MAX_VEL = 220.0f;
static const float PHYS_MAX_ACC = 270.0f;

static const float PHYS_MAX_ROT_VEL = 1.0f;
static const float PHYS_MAX_ROT_ACC = 5.0f;

struct PhysicsData : public Trackable
{
	PhysicsData(
		const Vector2& vel
		, const Vector2& acc
		, float rotVel
		, float rotAcc
		, float maxSpeed = PHYS_MAX_VEL
		, float maxAcc = PHYS_MAX_ACC
		, float maxRotVel = PHYS_MAX_ROT_VEL
		, float theMaxRotAcc = PHYS_MAX_ROT_ACC)
		: vel(vel)
		, acc(acc)
		, rotVel(rotVel)
		, rotAcc(rotAcc)
		, maxSpeed(maxSpeed)
		, maxAcc(maxAcc)
		, maxRotSpeed(maxRotVel)
		, maxRotAcc(rotAcc)
	{};

	PhysicsData()
		: vel(Vector2::ZERO)
		, acc(Vector2::ZERO)
		, rotVel(0.0f)
		, rotAcc(0.0f)
		, maxSpeed(PHYS_MAX_VEL)
		, maxAcc(PHYS_MAX_ACC)
		, maxRotSpeed(PHYS_MAX_ROT_VEL)
		, maxRotAcc(PHYS_MAX_ROT_ACC)
	{};

	Vector2 vel;
	Vector2 acc;
	float rotVel;
	float rotAcc;
	float maxSpeed;
	float maxAcc;
	float maxRotSpeed;
	float maxRotAcc;
};

const PhysicsData ZERO_PHYSICS_DATA;

class PhysicsComponent :public Component
{
public:

	void	setData(const PhysicsData& data) { m_physicsData = data; };
	void	modData(const PhysicsData& data);

	const PhysicsData&	getData() const { return m_physicsData; };
	const Vector2&		getVelocity() const { return m_physicsData.vel; };
	const Vector2&		getAcceleration() const { return m_physicsData.acc; };

	float	getRotationalVelocity() const { return m_physicsData.rotVel; };
	float	getRotationalAcceleration() const { return m_physicsData.rotAcc; };

private:
	PhysicsData m_physicsData;
	ComponentID m_positionID;

	PhysicsComponent(
		const ComponentID& id,
		const ComponentID& posID) :
		Component(id),
		m_positionID(posID) {};

	~PhysicsComponent() {};

	void integrate(TransformComponent& posComponent, float elapsedTime);

	friend class ComponentManager;
};

#endif