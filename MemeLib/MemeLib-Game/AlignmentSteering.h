#ifndef _ALIGNMENT_STEERING_H_
#define _ALIGNMENT_STEERING_H_

#include <Trackable.h>
#include "Steering.h"

class AlignmentSteering : public Steering
{
public:
	AlignmentSteering(
		const UnitID& ownerID, 
		float radius);

	virtual Steering* getSteering();

	inline float getRadius() const { return m_radius; }
	inline void setRadius(float radius) { m_radius = radius; }

private:
	float m_radius;
};

#endif