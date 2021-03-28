#include "GYCube.h"

GYCube::GYCube(
	Texture & texture, Texture & normalMapTexture,
	TextureRegion& topTextureRegion, TextureRegion& sideTextureRegion, TextureRegion& bottomTextureRegion,
	Transform& transform)
	: Renderable(texture), normalMapTexture(normalMapTexture)
{
	this->transform = transform;

	mesh = Cube(topTextureRegion, sideTextureRegion, bottomTextureRegion).CreateCubeMesh();
}

GYCube::~GYCube()
{
}

void GYCube::Draw(bool bindOwnTexture)
{
	normalMapTexture.Bind(1);
	Renderable::Draw(bindOwnTexture);
}