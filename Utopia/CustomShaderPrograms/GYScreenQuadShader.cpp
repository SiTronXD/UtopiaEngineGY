#include "GYScreenQuadShader.h"

GYScreenQuadShader::GYScreenQuadShader()
{
	std::string vertexShaderFileName = "./Resources/Shaders/GYScreenQuadVertexShader.glsl";
	std::string fragmentShaderFileName = "./Resources/Shaders/GYScreenQuadFragmentShader.glsl";

	// Attributes
	AddAttributeName("position");
	AddAttributeName("texCoord");

	// Uniforms
	AddUniformName("diffuseTexture");
	AddUniformName("renderedReflectanceTexture");
	AddUniformName("reflectanceTexture");

	InitShader(vertexShaderFileName, fragmentShaderFileName);
}


GYScreenQuadShader::~GYScreenQuadShader()
{
}

void GYScreenQuadShader::Update(const Camera& camera)
{
	Bind();

	glm::mat4 projectionMatrix = camera.GetProjectionMatrix();

	// Textures
	glUniform1i(uniforms["diffuseTexture"], 0);
	glUniform1i(uniforms["renderedReflectanceTexture"], 1);
	glUniform1i(uniforms["reflectanceTexture"], 2);
}