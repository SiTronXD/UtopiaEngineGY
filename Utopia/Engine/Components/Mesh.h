#pragma once

#include <GL/glew.h>
#include "../Vertex.h"
#include "../Loaders/obj_loader.h"
#include "../Model.h"

#include <iostream>

class Mesh
{
private:
	Mesh(const Mesh& other) {}

	void InitMesh(Model& model);

	enum
	{
		VBO_POSITION,
		VBO_TEXCOORD,
		VBO_NORMAL,
		VBO_TANGENT,
		VBO_BITANGENT,

		VBO_INDEX,

		NUM_BUFFERS
	};

	GLuint vertexArrayObject;
	GLuint vertexBufferObjects[NUM_BUFFERS];

	unsigned int drawCount;

public:
	Mesh();
	Mesh(Vertex* vertices, unsigned int numVertices,
		unsigned int* indices, unsigned int numIndices);
	Mesh(const std::string& fileName);
	virtual ~Mesh();

	void Draw();
};