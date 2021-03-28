#include <iostream>
#include <GL/glew.h>
#include "Display.h"

int Display::width;
int Display::height;

Display::Display(int width, int height, const std::string& title, Input& input)
	: input(input)
{
	this->width = width;
	this->height = height;

	SDL_Init(SDL_INIT_EVERYTHING);

	SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_BUFFER_SIZE, 32);
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 16);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

	window = SDL_CreateWindow(
		title.c_str(), 
		SDL_WINDOWPOS_CENTERED, 
		SDL_WINDOWPOS_CENTERED, 
		width, 
		height, 
		SDL_WINDOW_OPENGL
	);

	glContext = SDL_GL_CreateContext(window);

	// Vsync (has to be set AFTER creating the context)
	SDL_GL_SetSwapInterval(1);

	GLenum status = glewInit();

	if (status != GLEW_OK)
	{
		std::cerr << "Glew failed to initialize" << std::endl;
	}

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);

	mouseFocus = true;
	keyboardFocus = true;
	focus = true;
	closed = false;
}

Display::~Display()
{
	// Context
	SDL_GL_DeleteContext(glContext);

	// Window
	SDL_DestroyWindow(window);

	// Subsystems
	SDL_Quit();
}

void Display::BindAsRenderTarget()
{
	glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);
	glViewport(0, 0, GetWidth(), GetHeight());
}

void Display::Clear(float r, float g, float b, float a)
{
	glClearColor(r, g, b, a);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Display::Update()
{
	// Swap display buffer
	SDL_GL_SwapWindow(window);

	SDL_Event e;

	input.Update();
	while (SDL_PollEvent(&e))
	{
		// Window events
		if (e.type == SDL_WINDOWEVENT)
		{
			switch (e.window.event)
			{
			// Lost focus
			case SDL_WINDOWEVENT_FOCUS_LOST:
				keyboardFocus = false;
				focus = false;
				break;

			// Gained focus
			case SDL_WINDOWEVENT_FOCUS_GAINED:
				keyboardFocus = true;
				break;

			// Mouse left window
			case SDL_WINDOWEVENT_LEAVE:
				mouseFocus = false;
				break;

			case SDL_WINDOWEVENT_ENTER:
				mouseFocus = true;
				break;
			}
		}
		// Close window
		else if (e.type == SDL_QUIT)
			closed = true;
		
		input.HandleEvent(e);
	}

	// Handle focus states
	if (keyboardFocus && mouseFocus)
		focus = true;

	// Lock mouse in the middle of the window
	input.UpdateLockMouse(focus);
}

int Display::GetWidth()
{
	return Display::width;
}

int Display::GetHeight()
{
	return Display::height;
}

bool Display::IsFocus()
{
	return focus;
}

bool Display::IsClosed()
{
	return closed;
}

SDL_Window * Display::GetWindow()
{
	return window;
}
