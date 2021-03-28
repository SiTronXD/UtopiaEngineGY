#include "NormalBufferShader.h"

NormalBufferShader::NormalBufferShader()
{
	std::string vertexShaderFileName = "./Resources/Shaders/NormalBufferVertexShader.glsl";
	std::string fragmentShaderFileName = "./Resources/Shaders/NormalBufferFragmentShader.glsl";

	// Attributes
	AddAttributeName("position");
	AddAttributeName("texCoord");
	AddAttributeName("normal");

	// Uniforms
	AddUniformName("modelMatrix");
	AddUniformName("viewMatrix");
	AddUniformName("projectionMatrix");
	AddUniformName("cameraPos");

	InitShader(vertexShaderFileName, fragmentShaderFileName);
}

NormalBufferShader::~NormalBufferShader()
{
}

void NormalBufferShader::Update(const Transform & transform, const Camera & camera)
{
	Bind();

	glm::mat4 modelMatrix = transform.GetModel();
	glm::mat4 viewMatrix = camera.GetViewMatrix();
	glm::mat4 projectionMatrix = camera.GetProjectionMatrix();

	// Matrices and vectors
	glUniformMatrix4fv(uniforms["modelMatrix"], 1, GL_FALSE, &modelMatrix[0][0]);
	glUniformMatrix4fv(uniforms["viewMatrix"], 1, GL_FALSE, &viewMatrix[0][0]);
	glUniformMatrix4fv(uniforms["projectionMatrix"], 1, GL_FALSE, &projectionMatrix[0][0]);
	glUniform3fv(uniforms["cameraPos"], 1, glm::value_ptr(camera.GetPosition()));
}
