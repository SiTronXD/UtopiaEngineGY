#include "Plane.h"

void Plane::CreatePlaneVertices(glm::vec2 texCoords[])
{
	glm::vec3 scl = transform.GetScale();

	// Face
	vertices[0] = Vertex(glm::vec3(-0.5f, 0.0f,  0.5f), texCoords[0], glm::vec3(0.0f, 1.0f, 0.0f));
	vertices[1] = Vertex(glm::vec3(-0.5f, 0.0f, -0.5f), texCoords[1], glm::vec3(0.0f, 1.0f, 0.0f));
	vertices[2] = Vertex(glm::vec3( 0.5f, 0.0f,  0.5f), texCoords[2], glm::vec3(0.0f, 1.0f, 0.0f));
	vertices[3] = Vertex(glm::vec3( 0.5f, 0.0f, -0.5f), texCoords[3], glm::vec3(0.0f, 1.0f, 0.0f));
}

Plane::Plane()
{
	this->transform = Transform(glm::vec3(0.0f), glm::vec3(0.0f), glm::vec3(1.0f));

	// Tex coords
	glm::vec2 texCoords[4];
	texCoords[0] = glm::vec2(0.0f, 0.0f);
	texCoords[1] = glm::vec2(0.0f, 1.0f);
	texCoords[2] = glm::vec2(1.0f, 0.0f);
	texCoords[3] = glm::vec2(1.0f, 1.0f);

	this->CreatePlaneVertices(texCoords);
}

Plane::Plane(TextureRegion & textureRegion, Transform& transform)
{
	this->transform = transform;

	float x1 = textureRegion.GetNormalizedX1(); // x
	float y1 = textureRegion.GetNormalizedY1(); // y
	float x2 = textureRegion.GetNormalizedX2(); // x + width
	float y2 = textureRegion.GetNormalizedY2(); // y + height

	// Tex coords
	glm::vec2 texCoords[4];
	texCoords[0] = glm::vec2(x1, y1);
	texCoords[1] = glm::vec2(x1, y2);
	texCoords[2] = glm::vec2(x2, y1);
	texCoords[3] = glm::vec2(x2, y2);

	this->CreatePlaneVertices(texCoords);
}


Plane::~Plane()
{
}

Mesh *Plane::CreatePlaneMesh()
{
	return new Mesh(vertices, sizeof(vertices) / sizeof(vertices[0]),
		indices, sizeof(indices) / sizeof(indices[0]));
}