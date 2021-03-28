#pragma once
#include "../Engine/Components/Shader.h"
class RenderReflectanceShader :
	public Shader
{
public:
	RenderReflectanceShader();
	virtual ~RenderReflectanceShader();

	virtual void Update(const Camera& camera);
};