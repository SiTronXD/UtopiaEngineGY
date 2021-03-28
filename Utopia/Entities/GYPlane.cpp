#include "GYPlane.h"

GYPlane::GYPlane(Texture & texture, 
	Texture & normalMapTexture, TextureRegion & textureRegion,
	Transform& transform)
	: Renderable(texture), normalMapTexture(normalMapTexture)
{
	this->transform = transform;
	mesh = Plane(textureRegion, this->transform).CreatePlaneMesh();
}

GYPlane::~GYPlane()
{
}

void GYPlane::Draw(bool bindOwnTexture)
{
	normalMapTexture.Bind(1);
	Renderable::Draw(bindOwnTexture);
}