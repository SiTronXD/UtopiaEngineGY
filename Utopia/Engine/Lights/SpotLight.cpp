#include "SpotLight.h"

SpotLight::SpotLight()
{
}

SpotLight::SpotLight(const glm::vec3 position, const glm::vec3 lookAtPosition, 
	glm::ivec2 smr)
{
	this->position = position;
	this->lookAtPosition = lookAtPosition;
	this->shadowMapResolution = smr;

	viewMatrix = glm::lookAt(position, lookAtPosition, glm::vec3(0.0f, 1.0f, 0.0f));
	perspectiveMatrix = glm::perspective(
		fov, 
		(float)shadowMapResolution.x / (float)shadowMapResolution.y, 
		near,
		far
	);
}

SpotLight::~SpotLight()
{
}

void SpotLight::SetShadowMapTexture(Texture * shadowMapTexture)
{
	this->shadowMapTexture = shadowMapTexture;
}

int SpotLight::GetShadowMapWidth()
{
	return this->shadowMapResolution.x;
}

int SpotLight::GetShadowMapHeight()
{
	return this->shadowMapResolution.y;
}

glm::vec3 & SpotLight::GetPosition()
{
	return this->position;
}

glm::mat4 & SpotLight::GetViewMatrix()
{
	return this->viewMatrix;
}

glm::mat4 & SpotLight::GetProjectionMatrix()
{
	return this->perspectiveMatrix;
}

glm::mat4 SpotLight::GetViewProjectionMatrix()
{
	return GetProjectionMatrix() * GetViewMatrix();
}

Texture & SpotLight::GetShadowMapTexture()
{
	return *shadowMapTexture;
}