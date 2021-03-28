#pragma once

#include "../Components/Mesh.h"
#include "../TextureRegion.h"

class Cube
{
private:
	void CreateCubeVertices(glm::vec2 texCoords[]);

	Vertex vertices[4 * 6];

	// COUNTER CLOCK WISE!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	unsigned int indices[3*12] =
	{
		 1,      0,      2,      // Front
		 3,      1,      2,
		 1 + 8,  0 + 8,  2 + 8,  // Left
		 3 + 8,  1 + 8,  2 + 8,
		 0 + 12, 1 + 12, 2 + 12, // Right
		 1 + 12, 3 + 12, 2 + 12,
		 0 + 4,  1 + 4,  2 + 4,  // Back
		 1 + 4,  3 + 4,  2 + 4,
		 1 + 16, 0 + 16, 2 + 16, // Top
		 3 + 16, 1 + 16, 2 + 16,
		 0 + 20, 1 + 20, 2 + 20, // Bottom
		 1 + 20, 3 + 20, 2 + 20
	};

	unsigned int invertedIndices[3 * 12] =
	{
		 1,      2,      0,       // Front
		 3,      2,      1,
		 1 + 8,  2 + 8,  0 + 8,   // Left
		 3 + 8,  2 + 8,  1 + 8,
		 0 + 12, 2 + 12, 1 + 12,  // Right
		 1 + 12, 2 + 12, 3 + 12,
		 0 + 4,  2 + 4,	 1 + 4,   // Back
		 1 + 4,  2 + 4,  3 + 4,
		 1 + 16, 2 + 16, 0 + 16,  // Top
		 3 + 16, 2 + 16, 1 + 16,
		 0 + 20, 2 + 20, 1 + 20,  // Bottom
		 1 + 20, 2 + 20, 3 + 20,
	};

public:
	Cube();
	Cube(TextureRegion& textureRegion);
	Cube(TextureRegion& topTextureRegion, TextureRegion& sideTextureRegion, TextureRegion& bottomTextureRegion);
	virtual ~Cube();

	Mesh* CreateCubeMesh();
	Mesh* CreateInvertedCubeMesh();
};