#pragma once

#include "Components/Texture.h"

class TextureRegion
{
private:
	Texture& texture;

	int x;
	int y;
	int regionWidth;
	int regionHeight;

	float normalizedX1;
	float normalizedY1;
	float normalizedX2;
	float normalizedY2;

public:
	TextureRegion(Texture& texture, int x, int y, 
		int width, int height);
	virtual ~TextureRegion();

	Texture& GetTexture() const;

	const int& GetRegionWidth() const;
	const int& GetRegionHeight() const;

	const float& GetNormalizedX1() const;
	const float& GetNormalizedY1() const;
	const float& GetNormalizedX2() const;
	const float& GetNormalizedY2() const;
};