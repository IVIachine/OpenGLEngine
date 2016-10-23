#ifndef _SEPARATION_STEERING_H_
#define _SEPARATION_STEERING_H_

#include <Trackable.h>
#include "Steering.h"

class SeparationSteering : public Steering
{
public:
	SeparationSteering(
		const UnitID& ownerID, 
		float radius);

	virtual Steering* getSteering();

	inline float getRadius() const { return m_radius; }
	inline void setRadius(float radius) { m_radius = radius; }

private:
	float m_radius;
};

#endif