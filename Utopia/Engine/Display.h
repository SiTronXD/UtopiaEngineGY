#pragma once

#include <string>
#include <SDL2/SDL.h>
#include "Input.h"

class Display
{
private:
	SDL_Window* window;
	SDL_GLContext glContext;

	Input& input;

	static int width;
	static int height;

	bool mouseFocus;
	bool keyboardFocus;
	bool focus;
	bool closed;

public:
	Display(int width, int height, const std::string& title, Input& input);
	virtual ~Display();

	static void BindAsRenderTarget();

	static void Clear(float r, float g, float b, float a);
	void Update();

	static int GetWidth();
	static int GetHeight();
	bool IsFocus();
	bool IsClosed();

	SDL_Window* GetWindow();
};