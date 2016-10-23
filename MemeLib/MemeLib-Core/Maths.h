#ifndef _MATHS_H_
#define _MATHS_H_

#include <math.h>

class Maths
{
public:
	static const float PI;
	static const float RAD_TO_DEG;
	static const float DEG_TO_RAD;

	static float clamp(float value, float min, float max);
	static float mapToRange(float value, float min, float max);
};

#endif // !_MATHS_H_
