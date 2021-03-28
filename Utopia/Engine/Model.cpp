#include "Model.h"



Model::Model()
{
}


Model::~Model()
{
}

void Model::CalculateNormals()
{
	// Give the same normal for a series of 3 vertices
	for (unsigned int i = 0; i < indices.size(); i += 3)
	{
		int i0 = indices[i];
		int i1 = indices[i + 1];
		int i2 = indices[i + 2];

		glm::vec3 v1 = positions[i1] - positions[i0];
		glm::vec3 v2 = positions[i2] - positions[i0];

		glm::vec3 normal = glm::normalize(glm::cross(v1, v2));

		normals[i0] += normal;
		normals[i1] += normal;
		normals[i2] += normal;
	}

	// Average the normals for each shared vertex
	for (unsigned int i = 0; i < positions.size(); i++)
		normals[i] = glm::normalize(normals[i]);
}

void Model::CalculateTangents()
{
	for (unsigned int i = 0; i < indices.size(); i += 3)
	{
		int i0 = indices[i];
		int i1 = indices[i + 1];
		int i2 = indices[i + 2];

		glm::vec3 normal0 = normals[i0];
		glm::vec3 normal1 = normals[i1];
		glm::vec3 normal2 = normals[i2];
		glm::vec3 currentNormal = glm::normalize(normal0 + normal1 + normal2);

		// Clear first
		tangents[i0] = glm::vec3(0.0f);
		tangents[i1] = glm::vec3(0.0f);
		tangents[i2] = glm::vec3(0.0f);

		biTangents[i0] = glm::vec3(0.0f);
		biTangents[i1] = glm::vec3(0.0f);
		biTangents[i2] = glm::vec3(0.0f);

		// Calculate tangent and bitangent
		glm::vec3 edge1 = positions[i1] - positions[i0];
		glm::vec3 edge2 = positions[i2] - positions[i0];
		glm::vec2 deltaUV1 = texCoords[i1] - texCoords[i0];
		glm::vec2 deltaUV2 = texCoords[i2] - texCoords[i0];

		float partInv = 1.0f / (deltaUV1.x * deltaUV2.y - deltaUV2.x * deltaUV1.y);

		// UV Matrix
		glm::mat2x2 uvMatrix = glm::mat2x2();
		uvMatrix[0] = glm::vec2( deltaUV2.y, -deltaUV1.y);
		uvMatrix[1] = glm::vec2(-deltaUV2.x,  deltaUV1.x);

		// Edge matrix
		glm::mat2x3 edgeMatrix = glm::mat2x3();
		edgeMatrix[0] = edge1;
		edgeMatrix[1] = edge2;

		// Multiply backwards
		glm::mat2x3 tbMatrix = edgeMatrix * uvMatrix * partInv;

		glm::vec3 tangent = glm::normalize(tbMatrix[0]);
		glm::vec3 biTangent = -glm::normalize(tbMatrix[1]);

		tangents[i0] += tangent;
		tangents[i1] += tangent;
		tangents[i2] += tangent;

		biTangents[i0] += biTangent;
		biTangents[i1] += biTangent;
		biTangents[i2] += biTangent;
	}

	// Average the tangents for each shared vertex
	for (unsigned int i = 0; i < positions.size(); i++)
	{
		tangents[i] = glm::normalize(tangents[i]);
		biTangents[i] = glm::normalize(biTangents[i]);
	}
}