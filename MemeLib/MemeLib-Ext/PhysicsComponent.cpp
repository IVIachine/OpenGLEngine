#include <cassert>

#include "PhysicsComponent.h"
#include "PositionComponent.h"

void PhysicsComponent::modData(const PhysicsData& data)
{
	mData.vel += data.vel;
	mData.acc += data.acc;
	mData.rotVel += data.rotVel;
	mData.rotAcc += data.rotAcc;
}

void PhysicsComponent::integrate(PositionComponent& posComponent, float elapsedTime)
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
		if(((mData.acc.x * mData.acc.x) + (mData.acc.y * mData.acc.y) + (mData.acc.z * mData.acc.z)) > (mData.maxAccMagnitude * mData.maxAccMagnitude))
		{
			glm::normalize(mData.acc);
			mData.acc *= mData.maxAccMagnitude;
		}
		if (mData.rotAcc > mData.maxRotAcc)
		{
			mData.maxRotAcc = mData.maxRotAcc;
		}
		else if (mData.rotAcc < -mData.maxRotAcc)
		{
			mData.rotAcc = -mData.maxRotAcc;
		}

		//apply accelerations to velocities
		mData.vel += (mData.acc * elapsedTime);
		mData.rotVel += (mData.rotAcc * elapsedTime);

		//cap velocities
		if (((mData.vel.x * mData.vel.x) + (mData.vel.y * mData.vel.y) + (mData.vel.z * mData.vel.z)) > (mData.maxSpeed * mData.maxSpeed))
		{
			glm::normalize(mData.vel);
			mData.vel *= mData.maxSpeed;
			mData.acc = Vec3(0,0,0);
		}
		if (mData.rotVel > mData.maxRotVel)
		{
			mData.rotVel = mData.maxRotVel;
			mData.rotAcc = 0.0f;
		}
		else if (mData.rotVel < -mData.maxRotVel)
		{
			mData.rotVel = -mData.maxRotVel;
			mData.rotAcc = 0.0f;
		}

		//apply velocities to position component
		posComponent.modPosition(mData.vel * elapsedTime);
		posComponent.modFacing(mData.rotVel * elapsedTime);
	}

}
