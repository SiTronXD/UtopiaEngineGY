#include "Camera.h"

Camera::Camera()
{

}

Camera::Camera(const glm::vec3& pos, float fov, float aspect, float zNear, float zFar, const glm::vec3 forward)
{
	this->perspectiveMatrix = glm::perspective(fov, aspect, zNear, zFar);
	this->position = pos;
	this->forward = glm::normalize(forward);
	this->up = glm::vec3(0, 1, 0);
}

Camera::~Camera()
{
}

void Camera::MovePosition(glm::vec3 delta)
{
	this->position += delta;
}

void Camera::Rotate(const glm::vec2& delta)
{
	glm::vec3 forward = this->GetForward();

	// Get horizontal angle, and move it
	float horizontalAngle = glm::degrees(atan2f(forward.x, forward.z));
	horizontalAngle -= delta.x;

	// Get vertical angle, and move it
	float verticalAngle = glm::degrees(asinf(forward.y));
	verticalAngle += delta.y;
	verticalAngle = SMath::Clamp(verticalAngle, -89.0f, 89.0f);

	// Move the "look-at" point
	forward = glm::vec3(
		sinf(glm::radians(horizontalAngle)) * cosf(glm::radians(verticalAngle)),
		sinf(glm::radians(verticalAngle)),
		cosf(glm::radians(horizontalAngle)) * cosf(glm::radians(verticalAngle))
	);

	this->SetForward(forward);
}

void Camera::SetForward(glm::vec3 forward)
{
	this->forward = forward;
}

void Camera::SetPosition(const glm::vec3 & position)
{
	this->position = position;
}

const glm::vec3 Camera::GetLeft()
{
	return glm::normalize(glm::cross(forward, up));
}

const glm::vec3 & Camera::GetForward() const
{
	return forward;
}

const glm::vec3 & Camera::GetPosition() const
{
	return position;
}

const glm::mat4 Camera::GetViewMatrix() const
{
	return glm::lookAt(position, position + forward, up);
}

const glm::mat4& Camera::GetProjectionMatrix() const
{
	return perspectiveMatrix;
}

const glm::mat4 Camera::GetViewProjection() const
{
	return GetProjectionMatrix() * GetViewMatrix();
}