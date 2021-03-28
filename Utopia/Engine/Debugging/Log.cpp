#include "Log.h"

Log::Log()
{
}

Log::~Log()
{
}

void Log::Write(std::string text)
{
	std::cout << text << std::endl;
}

void Log::CheckShaderError(GLuint shader, GLuint flag, bool isProgram, const std::string& errorMessage)
{
	GLint success = 0;
	GLchar error[1024] = { 0 };

	if (isProgram)
		glGetProgramiv(shader, flag, &success);
	else
		glGetShaderiv(shader, flag, &success);

	if (success == GL_FALSE)
	{
		if (isProgram)
			glGetProgramInfoLog(shader, sizeof(error), NULL, error);
		else
			glGetShaderInfoLog(shader, sizeof(error), NULL, error);

		std::cerr << errorMessage << ": '" << error << "'" << std::endl;
	}
}

std::string Log::ToStr(float f)
{
	return std::to_string(f);
}

std::string Log::ToStr(float f1, float f2)
{
	return std::to_string(f1) + "," + std::to_string(f2);
}

std::string Log::ToStr(float f1, float f2, float f3)
{
	return std::to_string(f1) + "," + std::to_string(f2) + "," + std::to_string(f3);
}
