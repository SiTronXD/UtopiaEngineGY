#pragma once

#include "../Engine/Components/Shader.h"

class SkyboxShader
	: public Shader
{
public:
	SkyboxShader();
	virtual ~SkyboxShader();

	virtual void Update(const Transform & transform, const Camera & camera);
};