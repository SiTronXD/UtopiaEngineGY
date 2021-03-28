#pragma once

#include "../Components/Transform.h"
#include "../Components/Mesh.h"
#include "../TextureRegion.h"
#include "../Vertex.h"

class Plane 
{
private:
	void CreatePlaneVertices(glm::vec2 texCoords[]);

	Vertex vertices[4];

	// COUNTER CLOCK WISE!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	unsigned int indices[3 * 2] =
	{
		 1, 0, 2, // Top
		 3, 1, 2
	};

	Transform transform;

public:
	Plane();
	Plane(TextureRegion& textureRegion, Transform& transform);
	virtual ~Plane();

	Mesh* CreatePlaneMesh();
};