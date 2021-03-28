#include "ScreenQuad.h"

ScreenQuad::ScreenQuad()
{
	Vertex vertices[4];
	
	vertices[0] = Vertex(glm::vec3(-1.0,  1.0, 0.0), glm::vec2(0.0, 1.0));
	vertices[1] = Vertex(glm::vec3(-1.0, -1.0, 0.0), glm::vec2(0.0, 0.0));
	vertices[2] = Vertex(glm::vec3( 1.0, -1.0, 0.0), glm::vec2(1.0, 0.0));
	vertices[3] = Vertex(glm::vec3( 1.0,  1.0, 0.0), glm::vec2(1.0, 1.0));

	/*
	vertices[0] = Vertex(glm::vec3(-0.7, 0.7, 0.0), glm::vec2(0.0, 1.0));
	vertices[1] = Vertex(glm::vec3(-0.7, -0.7, 0.0), glm::vec2(0.0, 0.0));
	vertices[2] = Vertex(glm::vec3(0.7, -0.7, 0.0), glm::vec2(1.0, 0.0));
	vertices[3] = Vertex(glm::vec3(0.7, 0.7, 0.0), glm::vec2(1.0, 1.0));
	*/

	unsigned int indices[3*2] =
	{
		0, 1, 2,
		0, 2, 3
	};

	mesh = new Mesh(
		vertices, 
		sizeof(vertices) / sizeof(vertices[0]),
		indices,
		sizeof(indices)/sizeof(indices[0])
	);
}

ScreenQuad::~ScreenQuad()
{
	delete mesh;
}

void ScreenQuad::Draw()
{
	mesh->Draw();
}
