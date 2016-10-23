#include <cassert>

#include "PhysicsComponent.h"
#include "TransformCOmponent.h"

void PhysicsComponent::modData(const PhysicsData& data)
{
	m_physicsData.vel += data.vel;
	m_physicsData.acc += data.acc;
	m_physicsData.rotVel += data.rotVel;
	m_physicsData.rotAcc += data.rotAcc;
}

void PhysicsComponent::integrate(TransformComponent& posComponent, float elapsedTime)
{
	//make sure elapsedTime is at least 0.0f
	assert(elapsedTime >= 0.0f);
	if (elapsedTime < 0.0f)
	{
		elapsedTime = 0.0f;
	}

	if (elapsedTime > 0.0f)//no need to do this for no elapsed time
	{
		//cap accelerations
		if (m_physicsData.acc.sqaredMagnitude() > (m_physicsData.maxAcc * m_physicsData.maxAcc))
		{
			m_physicsData.acc.normalize();
			m_physicsData.acc *= m_physicsData.maxAcc;
		}
		if (m_physicsData.rotAcc > m_physicsData.maxRotAcc)
		{
			m_physicsData.maxRotAcc = m_physicsData.maxRotAcc;
		}
		else if (m_physicsData.rotAcc < -m_physicsData.maxRotAcc)
		{
			m_physicsData.rotAcc = -m_physicsData.maxRotAcc;
		}

		//apply accelerations to velocities
		m_physicsData.vel += (m_physicsData.acc * elapsedTime);
		m_physicsData.rotVel += (m_physicsData.rotAcc * elapsedTime);

		//cap velocities
		if (m_physicsData.vel.sqaredMagnitude() > (m_physicsData.maxSpeed * m_physicsData.maxSpeed) )
		{
			m_physicsData.vel.normalize();
			m_physicsData.vel *= m_physicsData.maxSpeed;
			m_physicsData.acc = Vector2::ZERO;
		}
		if (m_physicsData.rotVel > m_physicsData.maxRotSpeed)
		{
			m_physicsData.rotVel = m_physicsData.maxRotSpeed;
			m_physicsData.rotAcc = 0.0f;
		}
		else if (m_physicsData.rotVel < -m_physicsData.maxRotSpeed)
		{
			m_physicsData.rotVel = -m_physicsData.maxRotSpeed;
			m_physicsData.rotAcc = 0.0f;
		}

		//apply velocities to position component
		posComponent.modPosition(m_physicsData.vel * elapsedTime);
		posComponent.modFacing(m_physicsData.rotVel * elapsedTime);
	}

}
