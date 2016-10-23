#include "Maths.h"

const float Maths::PI = 3.1415926535897932384626433832795028841971693993751058209749445923078164062862089986280348f;
const float Maths::RAD_TO_DEG = (180.0f / PI);
const float Maths::DEG_TO_RAD = (PI / 180.0f);

float Maths::clamp(float value, float min, float max)
{
	if (value < min)
		return min;

	if (value > max)
		return max;

	return value;
}

float Maths::mapToRange(float value, float min, float max)
{
	float TWO_MAX = (max + max);

	return min + (float)fmod(TWO_MAX + fmod(value + max, TWO_MAX), TWO_MAX);
}