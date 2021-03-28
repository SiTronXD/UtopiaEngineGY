#include "Cube.h"

void Cube::CreateCubeVertices(glm::vec2 texCoords[])
{
	// Front face
	vertices[0] = Vertex(glm::vec3(-0.5f, -0.5f, 0.5f), texCoords[0], glm::vec3(0.0f, 0.0f, 1.0f));
	vertices[1] = Vertex(glm::vec3(-0.5f, 0.5f, 0.5f),  texCoords[1], glm::vec3(0.0f, 0.0f, 1.0f));
	vertices[2] = Vertex(glm::vec3(0.5f, -0.5f, 0.5f),  texCoords[2], glm::vec3(0.0f, 0.0f, 1.0f));
	vertices[3] = Vertex(glm::vec3(0.5f, 0.5f, 0.5f),   texCoords[3], glm::vec3(0.0f, 0.0f, 1.0f));

	// Back face
	vertices[4] = Vertex(glm::vec3(-0.5f, -0.5f, -0.5f), texCoords[4], glm::vec3(0.0f, 0.0f, -1.0f));
	vertices[5] = Vertex(glm::vec3(-0.5f, 0.5f, -0.5f),  texCoords[5], glm::vec3(0.0f, 0.0f, -1.0f));
	vertices[6] = Vertex(glm::vec3(0.5f, -0.5f, -0.5f),  texCoords[6], glm::vec3(0.0f, 0.0f, -1.0f));
	vertices[7] = Vertex(glm::vec3(0.5f, 0.5f, -0.5f),   texCoords[7], glm::vec3(0.0f, 0.0f, -1.0f));

	// Left face
	vertices[8] = Vertex(glm::vec3(-0.5f, -0.5f, -0.5f), texCoords[8],  glm::vec3(-1.0f, 0.0f, 0.0f));
	vertices[9] = Vertex(glm::vec3(-0.5f, 0.5f, -0.5f),  texCoords[9],  glm::vec3(-1.0f, 0.0f, 0.0f));
	vertices[10] = Vertex(glm::vec3(-0.5f, -0.5f, 0.5f), texCoords[10], glm::vec3(-1.0f, 0.0f, 0.0f));
	vertices[11] = Vertex(glm::vec3(-0.5f, 0.5f, 0.5f),  texCoords[11], glm::vec3(-1.0f, 0.0f, 0.0f));

	// Right face
	vertices[12] = Vertex(glm::vec3(0.5f, -0.5f, -0.5f), texCoords[12],glm::vec3(1.0f, 0.0f, 0.0f));
	vertices[13] = Vertex(glm::vec3(0.5f, 0.5f, -0.5f), texCoords[13], glm::vec3(1.0f, 0.0f, 0.0f));
	vertices[14] = Vertex(glm::vec3(0.5f, -0.5f, 0.5f), texCoords[14], glm::vec3(1.0f, 0.0f, 0.0f));
	vertices[15] = Vertex(glm::vec3(0.5f, 0.5f, 0.5f), texCoords[15],  glm::vec3(1.0f, 0.0f, 0.0f));

	// Top face
	vertices[16] = Vertex(glm::vec3(-0.5f, 0.5f, 0.5f),  texCoords[16], glm::vec3(0.0f, 1.0f, 0.0f));
	vertices[17] = Vertex(glm::vec3(-0.5f, 0.5f, -0.5f), texCoords[17], glm::vec3(0.0f, 1.0f, 0.0f));
	vertices[18] = Vertex(glm::vec3(0.5f, 0.5f, 0.5f), texCoords[18],   glm::vec3(0.0f, 1.0f, 0.0f));
	vertices[19] = Vertex(glm::vec3(0.5f, 0.5f, -0.5f), texCoords[19],  glm::vec3(0.0f, 1.0f, 0.0f));

	// Bottom face
	vertices[20] = Vertex(glm::vec3(-0.5f, -0.5f, 0.5f),  texCoords[20], glm::vec3(0.0f, -1.0f, 0.0f));
	vertices[21] = Vertex(glm::vec3(-0.5f, -0.5f, -0.5f), texCoords[21], glm::vec3(0.0f, -1.0f, 0.0f));
	vertices[22] = Vertex(glm::vec3(0.5f, -0.5f, 0.5f), texCoords[22],   glm::vec3(0.0f, -1.0f, 0.0f));
	vertices[23] = Vertex(glm::vec3(0.5f, -0.5f, -0.5f), texCoords[23],  glm::vec3(0.0f, -1.0f, 0.0f));
}

// Choose the whole texture, for all sides, as default
Cube::Cube()
{
	// Front face
	glm::vec2 texCoords[6*4];
	texCoords[0] = glm::vec2(0.0f, 0.0f);
	texCoords[1] = glm::vec2(0.0f, 1.0f);
	texCoords[2] = glm::vec2(1.0f, 0.0f);
	texCoords[3] = glm::vec2(1.0f, 1.0f);

	// Back face
	texCoords[4] = glm::vec2(1.0f, 0.0f);
	texCoords[5] = glm::vec2(1.0f, 1.0f);
	texCoords[6] = glm::vec2(0.0f, 0.0f);
	texCoords[7] = glm::vec2(0.0f, 1.0f);

	// Left face
	texCoords[8] = glm::vec2(0.0f, 0.0f);
	texCoords[9] = glm::vec2(0.0f, 1.0f);
	texCoords[10] = glm::vec2(1.0f, 0.0f);
	texCoords[11] = glm::vec2(1.0f, 1.0f);

	// Right face
	texCoords[12] = glm::vec2(1.0f, 0.0f);
	texCoords[13] = glm::vec2(1.0f, 1.0f);
	texCoords[14] = glm::vec2(0.0f, 0.0f);
	texCoords[15] = glm::vec2(0.0f, 1.0f);

	// Top face
	texCoords[16] = glm::vec2(0.0f, 0.0f);
	texCoords[17] = glm::vec2(0.0f, 1.0f);
	texCoords[18] = glm::vec2(1.0f, 0.0f);
	texCoords[19] = glm::vec2(1.0f, 1.0f);

	// Bottom face
	texCoords[20] = glm::vec2(1.0f, 0.0f);
	texCoords[21] = glm::vec2(1.0f, 1.0f);
	texCoords[22] = glm::vec2(0.0f, 0.0f);
	texCoords[23] = glm::vec2(0.0f, 1.0f);

	this->CreateCubeVertices(texCoords);
}

// Choose the specified texture region for all sides
Cube::Cube(TextureRegion & textureRegion)
{
	float x1 = textureRegion.GetNormalizedX1(); // x
	float y1 = textureRegion.GetNormalizedY1(); // y
	float x2 = textureRegion.GetNormalizedX2(); // x + width
	float y2 = textureRegion.GetNormalizedY2(); // y + height

	// Front face
	glm::vec2 texCoords[6 * 4];
	texCoords[0] = glm::vec2(x1, y1);
	texCoords[1] = glm::vec2(x1, y2);
	texCoords[2] = glm::vec2(x2, y1);
	texCoords[3] = glm::vec2(x2, y2);

	// Back face
	texCoords[4] = glm::vec2(x2, y1);
	texCoords[5] = glm::vec2(x2, y2);
	texCoords[6] = glm::vec2(x1, y1);
	texCoords[7] = glm::vec2(x1, y2);

	// Left face
	texCoords[8] = glm::vec2(x1, y1);
	texCoords[9] = glm::vec2(x1, y2);
	texCoords[10] = glm::vec2(x2, y1);
	texCoords[11] = glm::vec2(x2, y2);

	// Right face
	texCoords[12] = glm::vec2(x2, y1);
	texCoords[13] = glm::vec2(x2, y2);
	texCoords[14] = glm::vec2(x1, y1);
	texCoords[15] = glm::vec2(x1, y2);

	// Top face
	texCoords[16] = glm::vec2(x1, y1);
	texCoords[17] = glm::vec2(x1, y2);
	texCoords[18] = glm::vec2(x2, y1);
	texCoords[19] = glm::vec2(x2, y2);

	// Bottom face
	texCoords[20] = glm::vec2(x2, y1);
	texCoords[21] = glm::vec2(x2, y2);
	texCoords[22] = glm::vec2(x1, y1);
	texCoords[23] = glm::vec2(x1, y2);

	this->CreateCubeVertices(texCoords);
}

Cube::Cube(TextureRegion & topTextureRegion, 
	TextureRegion & sideTextureRegion, TextureRegion & bottomTextureRegion)
{
	float top_x1 = topTextureRegion.GetNormalizedX1(); // x
	float top_y1 = topTextureRegion.GetNormalizedY1(); // y
	float top_x2 = topTextureRegion.GetNormalizedX2(); // x + width
	float top_y2 = topTextureRegion.GetNormalizedY2(); // y + height

	float side_x1 = sideTextureRegion.GetNormalizedX1(); // x
	float side_y1 = sideTextureRegion.GetNormalizedY1(); // y
	float side_x2 = sideTextureRegion.GetNormalizedX2(); // x + width
	float side_y2 = sideTextureRegion.GetNormalizedY2(); // y + height

	float bottom_x1 = bottomTextureRegion.GetNormalizedX1(); // x
	float bottom_y1 = bottomTextureRegion.GetNormalizedY1(); // y
	float bottom_x2 = bottomTextureRegion.GetNormalizedX2(); // x + width
	float bottom_y2 = bottomTextureRegion.GetNormalizedY2(); // y + height

	// Front face
	glm::vec2 texCoords[6 * 4];
	texCoords[0] = glm::vec2(side_x1, side_y1);
	texCoords[1] = glm::vec2(side_x1, side_y2);
	texCoords[2] = glm::vec2(side_x2, side_y1);
	texCoords[3] = glm::vec2(side_x2, side_y2);

	// Back face
	texCoords[4] = glm::vec2(side_x2, side_y1);
	texCoords[5] = glm::vec2(side_x2, side_y2);
	texCoords[6] = glm::vec2(side_x1, side_y1);
	texCoords[7] = glm::vec2(side_x1, side_y2);

	// Left face
	texCoords[8] = glm::vec2(side_x1, side_y1);
	texCoords[9] = glm::vec2(side_x1, side_y2);
	texCoords[10] = glm::vec2(side_x2, side_y1);
	texCoords[11] = glm::vec2(side_x2, side_y2);

	// Right face
	texCoords[12] = glm::vec2(side_x2, side_y1);
	texCoords[13] = glm::vec2(side_x2, side_y2);
	texCoords[14] = glm::vec2(side_x1, side_y1);
	texCoords[15] = glm::vec2(side_x1, side_y2);

	// Top face
	texCoords[16] = glm::vec2(top_x1, top_y1);
	texCoords[17] = glm::vec2(top_x1, top_y2);
	texCoords[18] = glm::vec2(top_x2, top_y1);
	texCoords[19] = glm::vec2(top_x2, top_y2);

	// Bottom face
	texCoords[20] = glm::vec2(bottom_x2, bottom_y1);
	texCoords[21] = glm::vec2(bottom_x2, bottom_y2);
	texCoords[22] = glm::vec2(bottom_x1, bottom_y1);
	texCoords[23] = glm::vec2(bottom_x1, bottom_y2);

	this->CreateCubeVertices(texCoords);
}

Cube::~Cube()
{

}

Mesh* Cube::CreateCubeMesh()
{
	return new Mesh(vertices, sizeof(vertices) / sizeof(vertices[0]),
		indices, sizeof(indices) / sizeof(indices[0]));
}

Mesh * Cube::CreateInvertedCubeMesh()
{
	return new Mesh(vertices, sizeof(vertices) / sizeof(vertices[0]),
		invertedIndices, sizeof(invertedIndices) / sizeof(invertedIndices[0]));
}
