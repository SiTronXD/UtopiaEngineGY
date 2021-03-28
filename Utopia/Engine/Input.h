#pragma once

#include <map>
#include <SDL2/SDL.h>
#include <glm/glm.hpp>
#include "AppHandler.h"
#include "Debugging/Log.h"

enum IK
{
	A,
	B,
	C,
	D,
	E,
	F,
	G,
	H,
	I,
	J,
	K,
	L,
	M,
	N,
	O,
	P,
	Q,
	R,
	S,
	T,
	U,
	V,
	W,
	X,
	Y,
	Z,
	ESCAPE,
	SHIFT_LEFT,
	ARROW_UP,
	ARROW_DOWN,
	ARROW_LEFT,
	ARROW_RIGHT,

	NUM_OF_KEYS
};

class Input
{
private:
	SDL_Window* window;

	// IK to SDLK
	std::map<unsigned int, unsigned int> keyToSdl;

	// SDLK
	std::map<unsigned int, bool> keyDown;
	std::map<unsigned int, bool> lastKeyDown;

	glm::vec2 mousePosition;
	glm::vec2 lastMousePosition;
	glm::vec2 mouseDelta;

	static const unsigned int maxMouseButtons = 2;
	bool mouseButtonDown[maxMouseButtons];
	bool lastMouseButtonDown[maxMouseButtons];

	static bool lockMouse;

	void Init();
	void UpdateMousePosition();

public:
	Input();
	virtual ~Input();

	void SetWindow(SDL_Window* window);

	void Update();
	void UpdateLockMouse(bool windowFocus);
	void HandleEvent(SDL_Event& e);

	static void SetLockMouse(bool lock);

	bool IsKeyDown(IK key);
	bool IsKeyJustPressed(IK key);
	bool IsMouseDown(int mouseButtonIndex);
	bool IsMouseJustPressed(int mouseButtonIndex);

	const glm::vec2& GetMousePosition() const;
	const glm::vec2& GetMouseDelta() const;
};