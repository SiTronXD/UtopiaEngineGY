#include "RayMarcherShader.h"



RayMarcherShader::RayMarcherShader()
{
	std::string vertexShaderFileName = "./Resources/Shaders/RayMarcherVertexShader.glsl";
	std::string fragmentShaderFileName = "./Resources/Shaders/RayMarcherFragmentShader.glsl";

	// Attributes
	AddAttributeName("position");
	AddAttributeName("texCoord");

	// Uniforms
	AddUniformName("time");
	AddUniformName("cameraPos");
	AddUniformName("cameraDir");

	for(int i = 0; i < 2; i++)
		AddUniformName("spherePositions[" + std::to_string(i) + "]");

	InitShader(vertexShaderFileName, fragmentShaderFileName);
}


RayMarcherShader::~RayMarcherShader()
{
}

void RayMarcherShader::Update(float time, glm::vec3 cameraPosition, 
	glm::vec3 cameraDirection, std::vector<glm::vec3> spherePositions)
{
	Bind();

	glUniform1f(uniforms["time"], time);
	glUniform3fv(uniforms["cameraPos"], 1, glm::value_ptr(cameraPosition));
	glUniform3fv(uniforms["cameraDir"], 1, glm::value_ptr(cameraDirection));

	for(unsigned int i = 0; i < spherePositions.size(); i++)
		glUniform3fv(uniforms["spherePositions[" + std::to_string(i) + "]"], 1, glm::value_ptr(spherePositions[i]));
}
