#include "ReflectanceDepthShader.h"

ReflectanceDepthShader::ReflectanceDepthShader()
{
	std::string vertexShaderFileName = "./Resources/Shaders/ReflectanceDepthVertexShader.glsl";
	std::string fragmentShaderFileName = "./Resources/Shaders/ReflectanceDepthFragmentShader.glsl";

	// Attributes
	AddAttributeName("position");
	AddAttributeName("texCoord");

	// Uniforms
	AddUniformName("modelMatrix");
	AddUniformName("viewMatrix");
	AddUniformName("projectionMatrix");
	AddUniformName("cameraPos");

	AddUniformName("diffuseTexture");

	InitShader(vertexShaderFileName, fragmentShaderFileName);
}

ReflectanceDepthShader::~ReflectanceDepthShader()
{
}

void ReflectanceDepthShader::Update(const Transform & transform, const Camera & camera)
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

	// Textures
	glUniform1i(uniforms["diffuseTexture"], 0);
}