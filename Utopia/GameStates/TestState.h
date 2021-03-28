#pragma once

#include "../Engine/GameState.h"
#include "../Engine/Game.h"

class GameState;
class PlayerSpectateController;
class Input;

class TestState :
	public GameState
{
private:
	Camera camera;

	Vertex vertices[4];
	Transform transform;

	PlayerSpectateController* spectateController;

	float counter;
	float counter2;

public:
	TestState(Input& input);
	virtual ~TestState();

	virtual void Init();
	virtual void HandleInput(double dt);
	virtual void Update(double dt);
	virtual void Draw();
};