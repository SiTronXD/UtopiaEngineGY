#pragma once

#include "../Engine/Components/Shader.h"

class ReflectShader
	: public Shader
{
public:
	ReflectShader();
	virtual ~ReflectShader();

	virtual void Update(const Transform & transform, const Camera & camera);
};