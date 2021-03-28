#pragma once

#include "../Engine/Components/Shader.h"

class ReflectanceDepthShader :
	public Shader
{
public:
	ReflectanceDepthShader();
	virtual ~ReflectanceDepthShader();

	virtual void Update(const Transform & transform, const Camera & camera);
};