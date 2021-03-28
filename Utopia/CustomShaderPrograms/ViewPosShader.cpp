#include "ViewPosShader.h"

ViewPosShader::ViewPosShader()
{
	std::string vertexShaderFileName = "./Resources/Shaders/ViewPosVertexShader.glsl";
	std::string fragmentShaderFileName = "./Resources/Shaders/ViewPosFragmentShader.glsl";

	// Attributes
	AddAttributeName("position");

	// Uniforms
	AddUniformName("modelMatrix");
	AddUniformName("viewMatrix");
	AddUniformName("projectionMatrix");

	InitShader(vertexShaderFileName, fragmentShaderFileName);
}


ViewPosShader::~ViewPosShader()
{
}

void ViewPosShader::Update(const Transform & transform, const Camera & camera)
{
	Bind();

	glm::mat4 modelMatrix = transform.GetModel();
	glm::mat4 viewMatrix = camera.GetViewMatrix();
	glm::mat4 projectionMatrix = camera.GetProjectionMatrix();

	// Matrices and vectors
	glUniformMatrix4fv(uniforms["modelMatrix"], 1, GL_FALSE, &modelMatrix[0][0]);
	glUniformMatrix4fv(uniforms["viewMatrix"], 1, GL_FALSE, &viewMatrix[0][0]);
	glUniformMatrix4fv(uniforms["projectionMatrix"], 1, GL_FALSE, &projectionMatrix[0][0]);
}