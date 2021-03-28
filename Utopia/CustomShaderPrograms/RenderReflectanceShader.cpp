#include "RenderReflectanceShader.h"

RenderReflectanceShader::RenderReflectanceShader()
{
	std::string vertexShaderFileName = "./Resources/Shaders/RenderReflectanceVertexShader.glsl";
	std::string fragmentShaderFileName = "./Resources/Shaders/RenderReflectanceFragmentShader.glsl";

	// Attributes
	AddAttributeName("position");
	AddAttributeName("texCoord");

	// Uniforms
	AddUniformName("projectionMatrix");
	AddUniformName("cameraPos");

	AddUniformName("diffuseTexture");
	AddUniformName("depthTexture");
	AddUniformName("reflectanceTexture");
	AddUniformName("normalBufferTexture");
	AddUniformName("viewPosTexture");

	InitShader(vertexShaderFileName, fragmentShaderFileName);
}

RenderReflectanceShader::~RenderReflectanceShader()
{
}

void RenderReflectanceShader::Update(const Camera& camera)
{
	Bind();

	glm::mat4 projectionMatrix = camera.GetProjectionMatrix();

	// Matrices
	glUniformMatrix4fv(uniforms["projectionMatrix"], 1, GL_FALSE, &projectionMatrix[0][0]);
	glUniform3fv(uniforms["cameraPos"], 1, glm::value_ptr(camera.GetPosition()));

	// Textures
	glUniform1i(uniforms["diffuseTexture"], 0);
	glUniform1i(uniforms["depthTexture"], 1);
	glUniform1i(uniforms["reflectanceTexture"], 2);
	glUniform1i(uniforms["normalBufferTexture"], 3);
	glUniform1i(uniforms["viewPosTexture"], 4);
}