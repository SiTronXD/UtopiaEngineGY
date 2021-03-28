#pragma once

#include "../Engine/DefaultPolygons/Renderable.h"
#include "../Engine/DefaultPolygons/Cube.h"

class GYCube 
	: public Renderable
{
private:
	Texture& normalMapTexture;

public:
	GYCube(
		Texture& texture, Texture& normalMapTexture,
		TextureRegion& topTextureRegion, TextureRegion& sideTextureRegion, TextureRegion& bottomTextureRegion,
		Transform& transform);
	~GYCube();

	virtual void Draw(bool bindOwnTexture = true);
};