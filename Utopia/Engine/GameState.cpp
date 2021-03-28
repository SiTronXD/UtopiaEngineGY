#include "GameState.h"

GameState::GameState(Input& input)
	: input(input)
{ }

GameState::~GameState()
{
	// Shaders
	for (unsigned int i = 0; i < shaders.size(); i++)
		delete shaders[i];

	// Meshes
	for (unsigned int i = 0; i < meshes.size(); i++)
		delete meshes[i];

	// Textures
	for (unsigned int i = 0; i < textures.size(); i++)
		delete textures[i];

	std::cout << "Cleared GameState Base Class" << std::endl;
}
