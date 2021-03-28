#include <fstream>
#include "Shader.h"

static std::string LoadShader(const std::string& fileName);
static GLuint CreateShader(const std::string& text, GLenum shaderType);

void Shader::AddAttributeName(const std::string newAttributeName)
{
	attributeNames.push_back(newAttributeName);
}

void Shader::AddUniformName(const std::string newUniformName)
{
	uniformNames.push_back(newUniformName);
}

Shader::Shader()
{
	
}

Shader::~Shader()
{
	for (unsigned int i = 0; i < NUM_SHADERS; i++)
	{
		glDetachShader(program, shaders[i]);
		glDeleteShader(shaders[i]);
	}

	glDeleteProgram(program);
}

void Shader::InitShader(const std::string& vertexShaderFileName, const std::string& fragmentShaderFileName)
{
	program = glCreateProgram();
	shaders[0] = CreateShader(LoadShader(vertexShaderFileName), GL_VERTEX_SHADER);
	shaders[1] = CreateShader(LoadShader(fragmentShaderFileName), GL_FRAGMENT_SHADER);

	for (unsigned int i = 0; i < NUM_SHADERS; i++)
		glAttachShader(program, shaders[i]);

	/*
	glBindAttribLocation(program, 0, "position");
	glBindAttribLocation(program, 1, "texCoord");
	glBindAttribLocation(program, 2, "normal");
	glBindAttribLocation(program, 3, "tangent");
	glBindAttribLocation(program, 4, "biTangent");
	*/

	for (int i = 0; i < attributeNames.size(); i++)
	{
		glBindAttribLocation(program, i, attributeNames[i].c_str());
	}

	glLinkProgram(program);
	Log::CheckShaderError(program, GL_LINK_STATUS, true, "Error: Program linking failed... name: " + vertexShaderFileName);

	glValidateProgram(program);
	Log::CheckShaderError(program, GL_VALIDATE_STATUS, true, "Error: Program is invalid... name: " + vertexShaderFileName);

	for (int i = 0; i < uniformNames.size(); i++)
	{
		uniforms[uniformNames[i]] = glGetUniformLocation(program, uniformNames[i].c_str());
	}
	
	/*
	uniforms[UNI_MODELMATRIX] = glGetUniformLocation(program, "modelMatrix");
	uniforms[UNI_VIEWMATRIX] = glGetUniformLocation(program, "viewMatrix");
	uniforms[UNI_PROJECTIONMATRIX] = glGetUniformLocation(program, "projectionMatrix");
	uniforms[UNI_CAMERAPOSITION] = glGetUniformLocation(program, "cameraPos");

	uniforms[UNI_DIFFUSETEXTURE] = glGetUniformLocation(program, "diffuseTexture");
	uniforms[UNI_NORMALMAPTEXTURE] = glGetUniformLocation(program, "normalMap");
	*/
}

void Shader::Bind()
{
	glUseProgram(program);
}

// Default shader uniform updates
void Shader::Update(const Transform& transform, const Camera& camera, SpotLight & spotLight)
{
	glm::mat4 modelMatrix = transform.GetModel();
	glm::mat4 viewMatrix = camera.GetViewMatrix();
	glm::mat4 projectionMatrix = camera.GetProjectionMatrix();

	// Matrices and vectors
	glUniformMatrix4fv(uniforms["modelMatrix"], 1, GL_FALSE, &modelMatrix[0][0]);
	glUniformMatrix4fv(uniforms["viewMatrix"], 1, GL_FALSE, &viewMatrix[0][0]);
	glUniformMatrix4fv(uniforms["projectionMatrix"], 1, GL_FALSE, &projectionMatrix[0][0]);
	glUniform3fv(uniforms["cameraPos"], 1, glm::value_ptr(camera.GetPosition()));
	glUniform3fv(uniforms["lightPos"], 1, glm::value_ptr(spotLight.GetPosition()));

	// Textures
	glUniform1i(uniforms["diffuseTexture"], 0);
	//glUniform1i(uniforms["normalMap"], 1);
}

static GLuint CreateShader(const std::string& text, GLenum shaderType)
{
	GLuint shader = glCreateShader(shaderType);

	if (shader == 0)
	{
		std::cerr << "Error: Shader creation failed" << std::endl;
	}

	const GLchar* shaderSourceStrings[1];
	GLint shaderSourceStringLengths[1];

	shaderSourceStrings[0] = text.c_str();
	shaderSourceStringLengths[0] = text.length();

	glShaderSource(shader, 1, shaderSourceStrings, shaderSourceStringLengths);
	glCompileShader(shader);

	Log::CheckShaderError(shader, GL_COMPILE_STATUS, false, "Error: Shader compilation failed");

	return shader;
}

static std::string LoadShader(const std::string& fileName)
{
	std::ifstream file;
	file.open((fileName).c_str());

	std::string output;
	std::string line;

	if (file.is_open())
	{
		while (file.good())
		{
			getline(file, line);
			output.append(line + "\n");
		}

		file.close();
	}
	else
	{
		std::cerr << "Unable to load shader: " << fileName << std::endl;
	}

	return output;
}