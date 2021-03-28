#pragma once

#include <cassert>
#include <iostream>
#include <string>
#include <GL/glew.h>

#include "../Loaders/stb_image.h"

enum TextureType
{
	DEFAULT,
	COLOR,
	DEPTH,
	CUBEMAP
};

class TextureData
{
private:
	void InitTextures(unsigned char *data, GLfloat filter, GLint textureClamp, TextureType tt);
	void InitCubeMap(unsigned char * imageData[], GLfloat filter, GLint textureClamp);
	void InitRenderTargets(TextureType tt);

	GLuint textureID;
	GLuint frameBuffer;
	GLuint renderBuffer;

	int width;
	int height;

public:
	TextureData(int width, int height, 
		unsigned char *data, GLfloat filter, GLint textureClamp, 
		TextureType tt);
	TextureData(int width, int height, unsigned char * data[], 
		GLfloat filter, GLint textureClamp);
	virtual ~TextureData();

	void Bind(GLenum target);
	void BindAsRenderTarget();
};

class Texture
{
private:
	Texture(const Texture& other) {}

	TextureData *textureData;

	int width;
	int height;

public:
	Texture();
	Texture(const std::string& fileName);
	Texture(const std::string& fileName, GLfloat textureFilter);
	Texture(const std::string fileNames[], GLfloat textureFilter);	// Only for cube maps
	Texture(int width, int height, GLfloat textureFilter, GLint textureClamp, TextureType tt = TextureType::COLOR);
	virtual ~Texture();

	void Bind(unsigned int unit, GLenum target = GL_TEXTURE_2D);
	void BindAsRenderTarget();

	void Clear(float alpha = 1.0f);

	const int& GetWidth() const;
	const int& GetHeight() const;
};