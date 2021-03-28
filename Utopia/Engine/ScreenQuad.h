#pragma once

#include "Components/Mesh.h"
#include "Components/Shader.h"

class ScreenQuad
{
private:
	Mesh* mesh;

public:
	ScreenQuad();
	virtual ~ScreenQuad();

	void Draw();
};