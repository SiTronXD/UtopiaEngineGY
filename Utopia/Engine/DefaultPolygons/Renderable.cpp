
#include "Renderable.h"

Renderable::Renderable(Texture& texture)
	: texture(texture)
{
	mesh = NULL;
}

Renderable::~Renderable()
{
	if (mesh != NULL)
		delete mesh;
}

void Renderable::Draw(bool bindOwnTexture)
{
	if(bindOwnTexture)
		texture.Bind(0);
	mesh->Draw();
}

void Renderable::SetTransform(const Transform& transform)
{
	this->transform = transform;
}

Transform & Renderable::GetTransform()
{
	return transform;
}
