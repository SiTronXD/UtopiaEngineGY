#include "TextureRegion.h"

TextureRegion::TextureRegion(Texture& texture, int x, int y, 
	int width, int height)
	: texture(texture)
{
	this->x = x;
	this->y = y;
	this->regionWidth = width;
	this->regionHeight = height;

	this->normalizedX1 = (float)x / (float)texture.GetWidth();
	this->normalizedY1 = (float)y / (float)texture.GetHeight();
	this->normalizedX2 = (float)(x + width) / (float)texture.GetWidth();
	this->normalizedY2 = (float)(y + height) / (float)texture.GetHeight();
}

TextureRegion::~TextureRegion()
{
}

Texture & TextureRegion::GetTexture() const
{
	return texture;
}

const int & TextureRegion::GetRegionWidth() const
{
	return regionWidth;
}

const int & TextureRegion::GetRegionHeight() const
{
	return regionHeight;
}

const float & TextureRegion::GetNormalizedX1() const
{
	return normalizedX1;
}

const float & TextureRegion::GetNormalizedY1() const
{
	return normalizedY1;
}

const float & TextureRegion::GetNormalizedX2() const
{
	return normalizedX2;
}

const float & TextureRegion::GetNormalizedY2() const
{
	return normalizedY2;
}
