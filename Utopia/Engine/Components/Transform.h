#pragma once

#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>

class Transform
{
private:
	glm::vec3 pos;
	glm::vec3 rot;
	glm::vec3 scale;

public:
	Transform(const glm::vec3& pos = glm::vec3(), const glm::vec3& rot = glm::vec3(), const glm::vec3& scale = glm::vec3(1.0f, 1.0f, 1.0f));
	virtual ~Transform();

	glm::mat4 GetModel() const;

	void SetPos(const glm::vec3& pos);
	void SetRot(const glm::vec3& rot);
	void SetScale(const glm::vec3& scale);

	inline glm::vec3& GetPos() { return pos; }
	inline glm::vec3& GetRot() { return rot; }
	inline glm::vec3& GetScale() { return scale; }
};