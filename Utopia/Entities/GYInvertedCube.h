#pragma once

#include "../Engine/DefaultPolygons/Renderable.h"
#include "../Engine/DefaultPolygons/Cube.h"

class GYInvertedCube
	: public Renderable
{
private:
	
public:
	GYInvertedCube(
		Texture& texture,
		TextureRegion& topTextureRegion, TextureRegion& sideTextureRegion, TextureRegion& bottomTextureRegion,
		Transform& transform);
	~GYInvertedCube();

	virtual void Draw(bool bindOwnTexture = true);
};

