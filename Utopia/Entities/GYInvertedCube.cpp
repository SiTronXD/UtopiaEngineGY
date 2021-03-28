#include "GYInvertedCube.h"


GYInvertedCube::GYInvertedCube(Texture & texture, TextureRegion & topTextureRegion, TextureRegion & sideTextureRegion, TextureRegion & bottomTextureRegion, Transform & transform)
	: Renderable(texture)
{
	this->transform = transform;

	mesh = Cube(topTextureRegion, sideTextureRegion, bottomTextureRegion).CreateCubeMesh();
}

GYInvertedCube::~GYInvertedCube()
{
}

void GYInvertedCube::Draw(bool bindOwnTexture)
{
	glCullFace(GL_FRONT); // Render inside of cube
	
	Renderable::Draw(bindOwnTexture);

	glCullFace(GL_BACK);
}