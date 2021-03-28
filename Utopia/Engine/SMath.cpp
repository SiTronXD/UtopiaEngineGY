#include "SMath.h"



SMath::SMath()
{
}


SMath::~SMath()
{
}

const float SMath::Clamp(float& val, float min, float max)
{
	if (val < min)
		return min;
	else if (val > max)
		return max;

	return val;
}

const float SMath::Round(const float & val)
{
	float absVal = Abs(val);
	float fractVal = absVal - (int)absVal;

	return fractVal >= 0.5f ? 
		(absVal + (1- absVal)) * Sign(val) : 
		(absVal - fractVal) * Sign(val);
}

const float SMath::Abs(const float & val)
{
	return val >= 0.0 ? val : -val;
}

const float SMath::Sign(const float & val)
{
	if (val > 0.0f)
		return 1.0f;
	if (val < 0.0f)
		return -1.0f;

	return 0.0f;
}
