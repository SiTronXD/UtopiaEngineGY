#pragma once

#include "GameState.h"

class GameState;

class GameStateManager
{
private:
	GameState* currentGameState;

	void ClearCurrentGameState();

public:
	GameStateManager();
	virtual ~GameStateManager();

	void SetGameState(GameState* nextGameState);

	void Init();
	void Update(double dt);
	void Draw();
};