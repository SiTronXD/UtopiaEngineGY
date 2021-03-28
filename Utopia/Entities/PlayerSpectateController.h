#pragma once

#include <iostream>
#include "../Engine/Camera.h"

class PlayerSpectateController

{
private:
	Camera* camera;

public:
	PlayerSpectateController()
	: camera(NULL)
	{}
	PlayerSpectateController(Camera* camera);
	~PlayerSpectateController();

	void Move(glm::vec2 dir, float speed);
	void Levitate(float dir, float speed);
	void Rotate(glm::vec2 dirDelta, float speed);
};