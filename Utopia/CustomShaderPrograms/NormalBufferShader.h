#pragma once

#include "../Engine/Components/Shader.h"

class NormalBufferShader :
	public Shader
{
public:
	NormalBufferShader();
	virtual ~NormalBufferShader();

	virtual void Update(const Transform & transform, const Camera & camera);
};