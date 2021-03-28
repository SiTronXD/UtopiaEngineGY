#pragma once
class SMath
{
public:
	SMath();
	virtual ~SMath();

	static const float Clamp(float& val, float min, float max);
	static const float Round(const float& val);
	static const float Abs(const float& val);
	static const float Sign(const float& val);
};