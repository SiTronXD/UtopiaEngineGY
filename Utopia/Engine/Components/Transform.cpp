#include "Transform.h"

Transform::Transform(const glm::vec3& pos, const glm::vec3& rot, const glm::vec3& scale)
	: pos(pos), rot(rot), scale(scale)
{

}

Transform::~Transform()
{

}

glm::mat4 Transform::GetModel() const
{
	glm::mat4 posMatrix = glm::translate(pos);
	glm::mat4 rotXMatrix = glm::rotate(glm::radians(rot.x), glm::vec3(1, 0, 0));
	glm::mat4 rotYMatrix = glm::rotate(glm::radians(rot.y), glm::vec3(0, 1, 0));
	glm::mat4 rotZMatrix = glm::rotate(glm::radians(rot.z), glm::vec3(0, 0, 1));
	glm::mat4 scaleMatrix = glm::scale(scale);

	glm::mat4 rotMatrix = rotZMatrix * rotYMatrix * rotXMatrix;

	return posMatrix * rotMatrix * scaleMatrix;
}

void Transform::SetPos(const glm::vec3& pos)
{
	this->pos = pos;
}

void Transform::SetRot(const glm::vec3& rot)
{
	this->rot = rot;
}

void Transform::SetScale(const glm::vec3& scale)
{
	this->scale = scale;
}