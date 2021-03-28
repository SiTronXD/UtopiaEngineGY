#pragma once

#include "../Engine/Components/Shader.h"

class NoLightShader :
	public Shader
{
public:
	NoLightShader();
	virtual ~NoLightShader();

	virtual void Update(const Transform& transform, const Camera& camera, SpotLight & spotLight);
};