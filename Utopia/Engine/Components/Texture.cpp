#include "Texture.h"

void TextureData::InitTextures(unsigned char * data, GLfloat filter, 
	GLint textureClamp, TextureType tt)
{
	glGenTextures(1, &textureID);

	glBindTexture(GL_TEXTURE_2D, textureID);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, textureClamp);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, textureClamp);

	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, filter);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, filter);

	if(tt == TextureType::DEFAULT || tt == TextureType::COLOR)
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
	else
		glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, width, height, 0, GL_DEPTH_COMPONENT, GL_FLOAT, data);
}

void TextureData::InitCubeMap(unsigned char* imageData[], GLfloat filter, GLint textureClamp)
{
	glGenTextures(1, &textureID);

	glBindTexture(GL_TEXTURE_CUBE_MAP, textureID);


	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, textureClamp);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, textureClamp);

	glTexParameterf(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, filter);
	glTexParameterf(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, filter);


	// Right, Left, Top, Bottom, Back, Front
	for (int i = 0; i < 6; i++)
		glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i,
			0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, imageData[i]);
}

void TextureData::InitRenderTargets(TextureType tt)
{
	// Figure out what kind of texture this is
	GLenum attachment = 0;
	if (tt == TextureType::DEFAULT)
		attachment = GL_NONE;
	else if (tt == TextureType::COLOR)
		attachment = GL_COLOR_ATTACHMENT0;
	else if (tt == TextureType::DEPTH)
		attachment = GL_DEPTH_ATTACHMENT;

	// Attachments is empty
	if (attachment == 0)
		return;

	GLenum drawBuffer;		// 32 is the max number of bound textures in OpenGL

	bool hasDepth = false;

	if (attachment == GL_NONE)
		return;

	// Check for depth attachment
	if (attachment == GL_DEPTH_ATTACHMENT)
	{
		drawBuffer = GL_NONE;

		hasDepth = true;
	}
	else
		drawBuffer = attachment;

	// Create frame buffer
	if (frameBuffer == 0)
	{
		glGenFramebuffers(1, &frameBuffer);
		glBindFramebuffer(GL_FRAMEBUFFER, frameBuffer);
	}

	glFramebufferTexture2D(GL_FRAMEBUFFER, attachment, GL_TEXTURE_2D, textureID, 0);

	// Something went wrong, and the frame buffer wasn't created
	if (frameBuffer == 0)
		return;

	// Create render buffer
	if (!hasDepth)
	{
		glGenRenderbuffers(1, &renderBuffer);
		glBindRenderbuffer(GL_RENDERBUFFER, renderBuffer);
		glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, width, height);
		glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, renderBuffer);
	}

	glDrawBuffers(1, &drawBuffer);

	// Make sure everything is ok
	if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
	{
		std::cerr << "Framebuffer creation failed!" << std::endl;
		assert(false);
	}

	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

TextureData::TextureData(int width, int height,
	unsigned char *data, GLfloat filter, GLint textureClamp,
	TextureType tt)
{
	this->width = width;
	this->height = height;
	this->frameBuffer = 0;
	this->renderBuffer = 0;

	this->textureID = 0;

	InitTextures(data, filter, textureClamp, tt);
	InitRenderTargets(tt);
}

TextureData::TextureData(int width, int height, unsigned char * data[], GLfloat filter, GLint textureClamp)
{
	this->width = width;
	this->height = height;
	this->frameBuffer = 0;
	this->renderBuffer = 0;

	this->textureID = 0;

	// Just to make it clear
	TextureType tt = TextureType::CUBEMAP;

	InitCubeMap(data, filter, textureClamp);
}

TextureData::~TextureData()
{
	if (textureID) glDeleteTextures(1, &textureID);

	if (frameBuffer) glDeleteFramebuffers(1, &frameBuffer);
	if (renderBuffer) glDeleteRenderbuffers(1, &renderBuffer);
}

void TextureData::Bind(GLenum target)
{
	glBindTexture(target, textureID);
}

void TextureData::BindAsRenderTarget()
{
	glBindFramebuffer(GL_FRAMEBUFFER, frameBuffer);
	glViewport(0, 0, width, height);
}

Texture::Texture()
{
	std::cerr << "You tried to use the default texture contructor... Don't do that! >:(" << std::endl;
}

Texture::Texture(const std::string& fileName)
	: Texture(fileName, GL_LINEAR)
{
	
}

Texture::Texture(const std::string& fileName, GLfloat textureFilter)
{
	int numComponents;
	unsigned char* imageData = 0;
	imageData = stbi_load(fileName.c_str(), &width, &height, &numComponents, 4);

	if (imageData == NULL)
	{
		std::cerr << "Texture loading failed for texture: " << fileName << std::endl;
		std::cerr << "Perhaps you tried to load a jpg?" << std::endl;
	}

	textureData = new TextureData(width, height, imageData, textureFilter, GL_REPEAT, TextureType::DEFAULT);
	
	stbi_image_free(imageData);
}

// For cube maps
Texture::Texture(const std::string fileNames[], GLfloat textureFilter)
{
	std::cout << "Init cube map" << std::endl;

	const int num_sides = 6;
	unsigned char * data[num_sides];
	for (int i = 0; i < num_sides; i++)
	{
		int numComponents;
		unsigned char* imageData = 0;
		imageData = stbi_load(fileNames[i].c_str(), &width, &height, &numComponents, 4);

		if (imageData == NULL)
		{
			std::cerr << "Texture loading failed for texture: " << fileNames[i] << std::endl;
			std::cerr << "Perhaps you tried to load a jpg?" << std::endl;
		}

		data[i] = imageData;
	}

	// Init cube map data
	textureData = new TextureData(width, height, data, textureFilter, GL_CLAMP_TO_EDGE);

	// Free memory
	for (int i = 0; i < num_sides; i++)
		stbi_image_free(data[i]);
}

Texture::Texture(int width, int height, GLfloat textureFilter, GLint textureClamp, 
	TextureType tt)
{
	this->width = width;
	this->height = height;

	unsigned char* imageData = 0;
	textureData = new TextureData(width, height, imageData, textureFilter, textureClamp, tt);

	/*
	if(tt == TextureType::COLOR)
		textureData = new TextureData(width, height, imageData, textureFilter, textureClamp, GL_COLOR_ATTACHMENT0);
	else if(tt == TextureType::DEPTH)
		textureData = new TextureData(width, height, imageData, textureFilter, textureClamp, GL_DEPTH_ATTACHMENT);*/
}

Texture::~Texture()
{
	delete textureData;
}

void Texture::Bind(unsigned int unit, GLenum target)
{
	assert(unit >= 0 && unit <= 31);

	glActiveTexture(GL_TEXTURE0 + unit);
	
	textureData->Bind(target);
}

void Texture::BindAsRenderTarget()
{
	textureData->BindAsRenderTarget();
}

void Texture::Clear(float alpha)
{
	glClearColor(0.1f, 0.1f, 0.1f, alpha);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

const int & Texture::GetWidth() const
{
	return width;
}

const int & Texture::GetHeight() const
{
	return height;
}