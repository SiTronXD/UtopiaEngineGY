#include "Vertex.h"

Vertex::Vertex(const glm::vec3& pos, const glm::vec2& texCoord, const glm::vec3& normal)
{
	this->pos = pos;
	this->texCoord = texCoord;
	this->normal = normal;
}


Vertex::~Vertex()
{
}
