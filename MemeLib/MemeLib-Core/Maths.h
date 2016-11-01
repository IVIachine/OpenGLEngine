#ifndef _MATHS_H_
#define _MATHS_H_

#include <math.h>
#include <random>
#include <time.h>

class Maths
{
public:
	static const float PI;
	static const float RAD_TO_DEG;
	static const float DEG_TO_RAD;

	static float clamp(float value, float min, float max);
	static float mapToRange(float value, float min, float max);

	static void seedRandom()
	{
		srand((unsigned)time(NULL));
	};

	static float genRandomFloat()
	{
		float r = (float)rand() / (float)RAND_MAX;
		return r;
	}

	static float genRandomBinomial()
	{
		return genRandomFloat() - genRandomFloat();
	}

	static float genRandomFloat(float a, float b)
	{
		float random = ((float)rand()) / (float)RAND_MAX;
		float diff = b - a;
		float r = random * diff;
		return a + r;
	}
};

#endif // !_MATHS_H_
