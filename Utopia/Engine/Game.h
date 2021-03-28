#pragma once

#include <chrono>

#include "Debugging/Log.h"
#include "Components/Shader.h"
#include "Components/Mesh.h"
#include "Components/Texture.h"
#include "Components/Transform.h"
#include "Camera.h"
#include "Display.h"
#include "AppHandler.h"
#include "GameStateManager.h"
#include "GameState.h"
#include "../GameStates/GYState.h"

class Game
{
private:
	Input input;

public:
	Game();
	virtual ~Game();

	void Run();

	static int GetScreenWidth();
	static int GetScreenHeight();
};