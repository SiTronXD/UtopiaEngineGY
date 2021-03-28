#pragma once

#include <iostream>
#include <string>

#include <GL/glew.h>

class Log
{
private:

public:
	Log();
	virtual ~Log();

	static void Write(std::string text);
	static void CheckShaderError(GLuint shader, GLuint flag, bool isProgram, const std::string& errorMessage);
	static std::string ToStr(float f);
	static std::string ToStr(float f1, float f2);
	static std::string ToStr(float f1, float f2, float f3);
};