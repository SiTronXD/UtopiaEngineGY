#pragma once

#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>

#include "SMath.h"

class Camera
{
private:
	glm::mat4 perspectiveMatrix;
	glm::vec3 position;
	glm::vec3 forward;
	glm::vec3 up;

public:
	Camera();
	Camera(const glm::vec3& pos, float fov, float aspect, float zNear, float zFar, const glm::vec3 forward = glm::vec3(0, 0, 1));
	virtual ~Camera();

	void MovePosition(glm::vec3 delta);
	void Rotate(const glm::vec2& delta);

	void SetForward(glm::vec3 forward);
	void SetPosition(const glm::vec3& position);

	const glm::vec3 GetLeft();
	const glm::vec3& GetForward() const;
	const glm::vec3& GetPosition() const;

	const glm::mat4 GetViewMatrix() const;
	const glm::mat4& GetProjectionMatrix() const;
	const glm::mat4 GetViewProjection() const;
};