#pragma once
#include "../Engine/Components/Shader.h"
class GYScreenQuadShader :
	public Shader
{
public:
	GYScreenQuadShader();
	virtual ~GYScreenQuadShader();

	virtual void Update(const Camera& camera);
};