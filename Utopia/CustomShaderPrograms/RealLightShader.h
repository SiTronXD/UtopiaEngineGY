#pragma once

#include "../Engine/Components/Shader.h"

class RealLightShader :
	public Shader
{
public:
	RealLightShader();
	virtual ~RealLightShader();

	virtual void Update(const Transform& transform, const Camera& camera, SpotLight & spotLight);
};