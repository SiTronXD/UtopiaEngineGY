#pragma once

#include "../Engine/Components/Shader.h"
#include "../Engine/Lights/SpotLight.h"

class ShadowMapShader :
	public Shader
{
public:
	ShadowMapShader();
	virtual ~ShadowMapShader();

	void Update(const Transform& transform, SpotLight& light);
};