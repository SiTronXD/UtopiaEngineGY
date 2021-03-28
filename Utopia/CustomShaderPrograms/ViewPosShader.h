#pragma once
#include "../Engine/Components/Shader.h"
class ViewPosShader :
	public Shader
{
public:
	ViewPosShader();
	virtual ~ViewPosShader();

	virtual void Update(const Transform & transform, const Camera & camera);
};

