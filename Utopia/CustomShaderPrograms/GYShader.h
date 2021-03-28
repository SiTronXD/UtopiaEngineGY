#pragma once

#include "../Engine/Components/Shader.h"

class GYShader :
	public Shader
{
public:
	GYShader();
	virtual ~GYShader();

	virtual void Update(const Transform & transform, const Camera & camera, SpotLight & spotLight);
};