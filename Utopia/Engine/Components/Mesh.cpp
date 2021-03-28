#include <vector>
#include "Mesh.h"

Mesh::Mesh()
{

}

Mesh::Mesh(const std::string& fileName)
{
	Model model = OBJModel(fileName).ToSitronModel();
	InitMesh(model);
}

void Mesh::InitMesh(Model& model)
{
	model.CalculateTangents();

	drawCount = model.indices.size();

	// VAO
	glGenVertexArrays(1, &vertexArrayObject);
	glBindVertexArray(vertexArrayObject);

	glGenBuffers(NUM_BUFFERS, vertexBufferObjects);

	// Position
	glBindBuffer(GL_ARRAY_BUFFER, vertexBufferObjects[VBO_POSITION]);
	glBufferData(GL_ARRAY_BUFFER, model.positions.size() * sizeof(model.positions[0]), &model.positions[0], GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

	// Texture coordinates
	glBindBuffer(GL_ARRAY_BUFFER, vertexBufferObjects[VBO_TEXCOORD]);
	glBufferData(GL_ARRAY_BUFFER, model.texCoords.size() * sizeof(model.texCoords[0]), &model.texCoords[0], GL_STATIC_DRAW);

	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, 0);

	// Normals
	glBindBuffer(GL_ARRAY_BUFFER, vertexBufferObjects[VBO_NORMAL]);
	glBufferData(GL_ARRAY_BUFFER, model.normals.size() * sizeof(model.normals[0]), &model.normals[0], GL_STATIC_DRAW);

	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, 0);

	// Tangents
	glBindBuffer(GL_ARRAY_BUFFER, vertexBufferObjects[VBO_TANGENT]);
	glBufferData(GL_ARRAY_BUFFER, model.tangents.size() * sizeof(model.tangents[0]), &model.tangents[0], GL_STATIC_DRAW);

	glEnableVertexAttribArray(3); // Index
	glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, 0, 0); // Index, num of *floats*

	// BiTangents
	glBindBuffer(GL_ARRAY_BUFFER, vertexBufferObjects[VBO_BITANGENT]);
	glBufferData(GL_ARRAY_BUFFER, model.biTangents.size() * sizeof(model.biTangents[0]), &model.biTangents[0], GL_STATIC_DRAW);

	glEnableVertexAttribArray(4); // Index
	glVertexAttribPointer(4, 3, GL_FLOAT, GL_FALSE, 0, 0); // Index, num of *floats*

	// Indices
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vertexBufferObjects[VBO_INDEX]);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, model.indices.size() * sizeof(model.indices[0]), &model.indices[0], GL_STATIC_DRAW);

	// Unbind the VAO
	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

Mesh::Mesh(Vertex* vertices, unsigned int numVertices,
	unsigned int* indices, unsigned int numIndices)
{
	Model model;

	for (unsigned int i = 0; i < numVertices; i++)
	{
		model.positions.push_back(*vertices[i].GetPos());
		model.texCoords.push_back(*vertices[i].GetTexCoord());
		model.normals.push_back(*vertices[i].GetNormal());
		model.tangents.push_back(*vertices[i].GetTangent());
		model.biTangents.push_back(*vertices[i].GetBiTangent());
	}

	for (unsigned int i = 0; i < numIndices; i++)
		model.indices.push_back(indices[i]);

	InitMesh(model);
}

Mesh::~Mesh()
{
	glDeleteVertexArrays(1, &vertexArrayObject);
}

void Mesh::Draw()
{
	glBindVertexArray(vertexArrayObject);

	/*
	GLenum error = glGetError();
	if (error != GL_NO_ERROR)
	{
		std::cout << "ERRROR: " << glewGetErrorString(error) << std::endl;
	}
	*/
	//glDrawArrays(GL_TRIANGLES, 0, drawCount);
	glDrawElements(GL_TRIANGLES, drawCount, GL_UNSIGNED_INT, 0);

	glBindVertexArray(0);
}