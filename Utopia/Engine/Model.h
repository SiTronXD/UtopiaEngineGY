#pragma once

#include <vector>
#include "glm/glm.hpp"

class Model
{
public:
	Model();
	~Model();

	std::vector<glm::vec3> positions;
	std::vector<glm::vec2> texCoords;
	std::vector<glm::vec3> normals;
	std::vector<glm::vec3> tangents;
	std::vector<glm::vec3> biTangents;
	std::vector<unsigned int> indices;

	void CalculateNormals();
	void CalculateTangents();
};