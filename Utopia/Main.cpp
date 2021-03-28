#include "Engine/Game.h"
#include <iostream>
#include <GL/glew.h>
#include "Engine/Display.h"
#include "Engine/Components/Shader.h"
#include "Engine/Components/Mesh.h"
#include "Engine/Components/Texture.h"
#include "Engine/Components/Transform.h"
#include "Engine/Camera.h"

int main(int argc, char** argv)
{
	{
		Game game;
		game.Run();
	}

	return 0;
}