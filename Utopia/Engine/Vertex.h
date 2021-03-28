#pragma once

#include "glm/glm.hpp"

class Vertex
{
private:
	glm::vec3 pos;
	glm::vec2 texCoord;
	glm::vec3 normal;
	glm::vec3 tangent;
	glm::vec3 biTangent;

public:
	Vertex() {}
	Vertex(const glm::vec3& pos, const glm::vec2& texCoord, const glm::vec3& normal = glm::vec3(0, 0, 0));
	~Vertex();

	inline glm::vec3* GetPos() { return &pos; }
	inline glm::vec2* GetTexCoord() { return &texCoord; }
	inline glm::vec3* GetNormal() { return &normal; }
	inline glm::vec3* GetTangent() { return &tangent; }
	inline glm::vec3* GetBiTangent() { return &biTangent; }
};