#pragma once

#include "../Engine/DefaultPolygons/Renderable.h"
#include "../Engine/DefaultPolygons/Plane.h"
#include "../CustomShaderPrograms/RealLightShader.h"

class GYPlane :
	public Renderable
{
private:
	Texture& normalMapTexture;

public:
	GYPlane(
		Texture& texture, Texture& normalMapTexture,
		TextureRegion& textureRegion, Transform& transform);
	virtual ~GYPlane();

	virtual void Draw(bool bindOwnTexture = true);
};