#pragma once

#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>

#include "../Components/Texture.h"
#include "../Debugging/Log.h"

class SpotLight
{
private:
	Texture *shadowMapTexture;

	glm::vec3 position;
	glm::vec3 lookAtPosition;

	glm::ivec2 shadowMapResolution;

	glm::mat4 perspectiveMatrix;
	glm::mat4 viewMatrix;

	const float fov = 90.0f;
	const float near = 0.01f;
	const float far = 100.0f;

public:
	SpotLight();
	SpotLight(const glm::vec3 position, const glm::vec3 lookAtPosition, glm::ivec2 smr);
	virtual ~SpotLight();

	void SetShadowMapTexture(Texture * shadowMapTexture);

	int GetShadowMapWidth();
	int GetShadowMapHeight();
	glm::vec3 & GetPosition();
	glm::mat4 & GetViewMatrix();
	glm::mat4 & GetProjectionMatrix();
	glm::mat4 GetViewProjectionMatrix();

	Texture & GetShadowMapTexture();
};