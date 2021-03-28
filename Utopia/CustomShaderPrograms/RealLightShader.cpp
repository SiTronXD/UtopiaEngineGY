#include "RealLightShader.h"

RealLightShader::RealLightShader()
{
	std::string vertexShaderFileName = "./Resources/Shaders/RealVertexShader.glsl";
	std::string fragmentShaderFileName = "./Resources/Shaders/RealFragmentShader.glsl";

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
	AddUniformName("lightVPMatrix");
	AddUniformName("cameraPos");
	AddUniformName("lightPos");
	AddUniformName("diffuseTexture");
	AddUniformName("normalMap");
	AddUniformName("shadowMap");

	InitShader(vertexShaderFileName, fragmentShaderFileName);
}

RealLightShader::~RealLightShader()
{
}

void RealLightShader::Update(const Transform & transform, const Camera & camera, SpotLight & spotLight)
{
	Bind();

	glm::mat4 modelMatrix = transform.GetModel();
	glm::mat4 viewMatrix = camera.GetViewMatrix();
	glm::mat4 projectionMatrix = camera.GetProjectionMatrix();

	// Matrices and vectors
	glUniformMatrix4fv(uniforms["modelMatrix"], 1, GL_FALSE, &modelMatrix[0][0]);
	glUniformMatrix4fv(uniforms["viewMatrix"], 1, GL_FALSE, &viewMatrix[0][0]);
	glUniformMatrix4fv(uniforms["projectionMatrix"], 1, GL_FALSE, &projectionMatrix[0][0]);
	glUniformMatrix4fv(uniforms["lightVPMatrix"], 1, GL_FALSE, &spotLight.GetViewProjectionMatrix()[0][0]);
	glUniform3fv(uniforms["cameraPos"], 1, glm::value_ptr(camera.GetPosition()));
	glUniform3fv(uniforms["lightPos"], 1, glm::value_ptr(spotLight.GetPosition()));

	// Textures
	glUniform1i(uniforms["diffuseTexture"], 0);
	glUniform1i(uniforms["normalMap"], 1);
	glUniform1i(uniforms["shadowMap"], 2);
}
