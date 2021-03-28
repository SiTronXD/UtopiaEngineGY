#include "GameStateManager.h"

void GameStateManager::ClearCurrentGameState()
{
	delete currentGameState;

	std::cout << "Cleared current game state" << std::endl;
}

GameStateManager::GameStateManager()
{
	currentGameState = NULL;
}

GameStateManager::~GameStateManager()
{
	ClearCurrentGameState();
}

void GameStateManager::SetGameState(GameState* nextGameState)
{
	ClearCurrentGameState();
	currentGameState = nextGameState;

	currentGameState->Init();
}

void GameStateManager::Init()
{
	if (currentGameState != NULL)
		currentGameState->Init();
}

void GameStateManager::Update(double dt)
{
	if (currentGameState != NULL)
	{
		currentGameState->HandleInput(dt);
		currentGameState->Update(dt);
	}
}

void GameStateManager::Draw()
{
	if (currentGameState != NULL)
		currentGameState->Draw();
}