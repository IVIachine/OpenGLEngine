#ifndef _FLOCK_STEERING_H_
#define _FLOCK_STEERING_H_

#include "FaceSteering.h"
#include "AlignmentSteering.h"
#include "CohesionSteering.h"
#include "SeparationSteering.h"

class FlockSteering : public Steering
{
public:
	FlockSteering(
		const UnitID& ownerID, 
		float aRadius = 150.0f,
		float cRadius = 150.0f,
		float sRadius = 150.0f,
		float aWeight = 1.0f,
		float cWeight = 1.0f,
		float sWeight = 1.0f);
	~FlockSteering();

	virtual Steering* getSteering();

	inline void setValues(float ar, float cr, float sr, float aw, float cw, float sw)
	{
		mp_align->setRadius(ar);
		mp_cohesion->setRadius(cr);
		mp_separation->setRadius(sr);

		/*
			The more I write in C, the more I love C++.
			When I write in C, makes me love C++ more and more.
		*/

		m_aWeight = aw;
		m_cWeight = cw;
		m_sWeight = sw;
	}

private:
	AlignmentSteering*	mp_align;
	CohesionSteering*	mp_cohesion;
	SeparationSteering*	mp_separation;
	FaceSteering*		mp_face;

	float m_aWeight;
	float m_cWeight;
	float m_sWeight;
};

#endif