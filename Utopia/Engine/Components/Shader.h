#pragma once

#include <string>
#include <map>
#include <vector>
#include <glm\gtc\type_ptr.hpp>

#include "../Debugging/Log.h"
#include "Transform.h"
#include "../Camera.h"
#include "../Lights/SpotLight.h"

class Shader
{
private:
	Shader(const Shader& other) {}

	static const unsigned int NUM_SHADERS = 2;

	enum
	{
		UNI_MODELMATRIX,
		UNI_VIEWMATRIX,
		UNI_PROJECTIONMATRIX,
		UNI_CAMERAPOSITION,
		UNI_DIFFUSETEXTURE,
		UNI_NORMALMAPTEXTURE,

		NUM_UNIFORMS
	};

	GLuint program;
	GLuint shaders[NUM_SHADERS];
	//GLuint uniforms[NUM_UNIFORMS];

	std::vector<std::string> attributeNames;
	std::vector<std::string> uniformNames;

protected:
	std::map<std::string, GLuint> uniforms;

	void AddAttributeName(const std::string newAttributeName);
	void AddUniformName(const std::string newUniformName);

public:
	Shader();
	virtual ~Shader();

	void InitShader(const std::string& vertexShaderFileName, const std::string& fragmentShaderFileName);

	void Bind();
	virtual void Update(const Transform& transform, const Camera& camera, SpotLight & spotlight);
};