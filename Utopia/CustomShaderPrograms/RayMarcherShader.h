#pragma once
#include "../Engine/Components/Shader.h"
class RayMarcherShader :
	public Shader
{
public:
	RayMarcherShader();
	virtual ~RayMarcherShader();

	virtual void Update(float time, glm::vec3 cameraPosition,
		glm::vec3 cameraDirection, std::vector<glm::vec3> spherePositions);
};