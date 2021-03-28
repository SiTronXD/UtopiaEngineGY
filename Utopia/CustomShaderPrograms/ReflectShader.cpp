#include "ReflectShader.h"

ReflectShader::ReflectShader()
{
	std::string vertexShaderFileName = "./Resources/Shaders/ReflectVertexShader.glsl";
	std::string fragmentShaderFileName = "./Resources/Shaders/ReflectFragmentShader.glsl";

	// Attributes
	AddAttributeName("position");
	AddAttributeName("texCoord");
	AddAttributeName("normal");
	AddAttributeName("tangent");
	AddAttributeName("biTangent");

	// Uniforms
	AddUniformName("modelMatrix");
	AddUniformName("viewMatrix");
	AddUniformName("projectionMatrix");
	AddUniformName("camPos");
	AddUniformName("skyboxTexture");

	InitShader(vertexShaderFileName, fragmentShaderFileName);
}

ReflectShader::~ReflectShader()
{
}

void ReflectShader::Update(const Transform & transform, const Camera & camera)
{
	Bind();

	glm::mat4 modelMatrix = transform.GetModel();
	glm::mat4 viewMatrix = camera.GetViewMatrix();
	glm::mat4 projectionMatrix = camera.GetProjectionMatrix();

	// Matrices and vectors
	glUniformMatrix4fv(uniforms["modelMatrix"], 1, GL_FALSE, &modelMatrix[0][0]);
	glUniformMatrix4fv(uniforms["viewMatrix"], 1, GL_FALSE, &viewMatrix[0][0]);
	glUniformMatrix4fv(uniforms["projectionMatrix"], 1, GL_FALSE, &projectionMatrix[0][0]);
	glUniform3fv(uniforms["camPos"], 1, glm::value_ptr(camera.GetPosition()));

	// Textures
	glUniform1i(uniforms["skyboxTexture"], 0);
}