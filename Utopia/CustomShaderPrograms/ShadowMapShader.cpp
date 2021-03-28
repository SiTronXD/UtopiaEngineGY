#include "ShadowMapShader.h"

ShadowMapShader::ShadowMapShader()
{
	std::string vertexShaderFileName = "./Resources/Shaders/ShadowMapVertexShader.glsl";
	std::string fragmentShaderFileName = "./Resources/Shaders/ShadowMapFragmentShader.glsl";

	// Attributes
	AddAttributeName("position");
	//AddAttributeName("texCoord");
	//AddAttributeName("normal");
	//AddAttributeName("tangent");
	//AddAttributeName("biTangent");

	// Uniforms
	AddUniformName("modelMatrix");
	AddUniformName("viewMatrix");
	AddUniformName("projectionMatrix");
	//AddUniformName("cameraPos");
	//AddUniformName("diffuseTexture");
	//AddUniformName("normalMap");

	InitShader(vertexShaderFileName, fragmentShaderFileName);
}

ShadowMapShader::~ShadowMapShader()
{
}

void ShadowMapShader::Update(const Transform & transform, SpotLight & light)
{
	Bind();

	glm::mat4 modelMatrix = transform.GetModel();
	glm::mat4 viewMatrix = light.GetViewMatrix();
	glm::mat4 projectionMatrix = light.GetProjectionMatrix();

	// Matrices and vectors
	glUniformMatrix4fv(uniforms["modelMatrix"], 1, GL_FALSE, &modelMatrix[0][0]);
	glUniformMatrix4fv(uniforms["viewMatrix"], 1, GL_FALSE, &viewMatrix[0][0]);
	glUniformMatrix4fv(uniforms["projectionMatrix"], 1, GL_FALSE, &projectionMatrix[0][0]);
}
