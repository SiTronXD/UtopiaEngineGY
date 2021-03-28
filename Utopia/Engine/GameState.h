#pragma once

#include <iostream>
#include <vector>

#include "Components/Shader.h"
#include "Components/Mesh.h"
#include "Components/Texture.h"
#include "Camera.h"

#include "Input.h"
#include "AppHandler.h"

class Shader;
class Mesh;
class Texture;

class Input;

class GameState
{
protected:
	std::vector<Shader*> shaders;
	std::vector<Mesh*> meshes;
	std::vector<Texture*> textures;

	Input& input;

public:
	GameState(Input& input);
	virtual ~GameState();

	virtual void Init() = 0;
	virtual void HandleInput(double dt) = 0;
	virtual void Update(double dt) = 0;
	virtual void Draw() = 0;
};