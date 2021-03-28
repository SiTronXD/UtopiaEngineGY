#include "Input.h"

bool Input::lockMouse;

Input::Input()
{
	Init();

	window = NULL;
	lockMouse = false;
}

Input::~Input()
{
}

void Input::Init()
{
	// Keyboard
	keyToSdl[IK::A] = SDLK_a;
	keyToSdl[IK::B] = SDLK_b;
	keyToSdl[IK::C] = SDLK_c;
	keyToSdl[IK::D] = SDLK_d;
	keyToSdl[IK::E] = SDLK_e;
	keyToSdl[IK::F] = SDLK_f;
	keyToSdl[IK::G] = SDLK_g;
	keyToSdl[IK::H] = SDLK_h;
	keyToSdl[IK::I] = SDLK_i;
	keyToSdl[IK::J] = SDLK_j;
	keyToSdl[IK::K] = SDLK_k;
	keyToSdl[IK::L] = SDLK_l;
	keyToSdl[IK::M] = SDLK_m;
	keyToSdl[IK::N] = SDLK_n;
	keyToSdl[IK::O] = SDLK_o;
	keyToSdl[IK::P] = SDLK_p;
	keyToSdl[IK::Q] = SDLK_q;
	keyToSdl[IK::R] = SDLK_r;
	keyToSdl[IK::S] = SDLK_s;
	keyToSdl[IK::T] = SDLK_t;
	keyToSdl[IK::U] = SDLK_u;
	keyToSdl[IK::V] = SDLK_v;
	keyToSdl[IK::W] = SDLK_w;
	keyToSdl[IK::X] = SDLK_x;
	keyToSdl[IK::Y] = SDLK_y;
	keyToSdl[IK::Z] = SDLK_z;
	keyToSdl[IK::ESCAPE] = SDLK_ESCAPE;
	keyToSdl[IK::SHIFT_LEFT] = SDLK_LSHIFT;
	keyToSdl[IK::ARROW_UP] = SDLK_UP;
	keyToSdl[IK::ARROW_DOWN] = SDLK_DOWN;
	keyToSdl[IK::ARROW_LEFT] = SDLK_LEFT;
	keyToSdl[IK::ARROW_RIGHT] = SDLK_RIGHT;

	// Init keys
	for (auto it = keyToSdl.begin(); it != keyToSdl.end(); it++)
	{
		keyDown[it->second] = false;
		lastKeyDown[it->second] = false;
	}

	// Init mouse buttons
	for (unsigned int i = 0; i < maxMouseButtons; i++)
	{
		mouseButtonDown[i] = false;
		lastMouseButtonDown[i] = false;
	}

	// Init mouse positions
	mousePosition = glm::vec2(-10.0f);
	lastMousePosition = glm::vec2(-10.0f);
	mouseDelta = glm::vec2(-10.0f);
}

void Input::UpdateMousePosition()
{
	int x, y;
	SDL_GetMouseState(&x, &y);
	mousePosition = glm::vec2(x, y);

	// First time
	if (lastMousePosition.x <= -5.0f)
		lastMousePosition = mousePosition;
}

void Input::SetWindow(SDL_Window * window)
{
	this->window = window;
}

// Updates "previous" handlers and nothing more :/
void Input::Update()
{
	// Last key down
	for (auto it = keyDown.begin(); it != keyDown.end(); it++)
	{
		lastKeyDown[it->first] = keyDown[it->first];
	}

	// Last mouse down
	for (unsigned int i = 0; i < maxMouseButtons; i++)
	{
		lastMouseButtonDown[i] = mouseButtonDown[i];
	}

	// Last mouse position
	lastMousePosition = mousePosition;
}

void Input::UpdateLockMouse(bool windowFocus)
{
	if (!windowFocus)
		return;

	// Lock mouse, and calculate mouseDelta
	if (lockMouse && window != NULL)
	{
		glm::vec2 windowMiddle = glm::vec2(
			AppHandler::GetScreenWidth() / 2,
			AppHandler::GetScreenHeight() / 2
		);

		mouseDelta = glm::vec2(mousePosition.x, mousePosition.y) - windowMiddle;

		SDL_WarpMouseInWindow(
			window,
			windowMiddle.x,
			windowMiddle.y
		);

		UpdateMousePosition();
	}
	else
		mouseDelta = mousePosition - lastMousePosition;
}

void Input::HandleEvent(SDL_Event & e)
{
	// Pressed down key
	if (e.type == SDL_KEYDOWN)
	{
		unsigned long key = e.key.keysym.sym;

		// Check if it exists
		if (keyDown.count(key))
		{
			keyDown[key] = true;
		}
		else
		{
			Log::Write("Could not find key!!");
		}
	}
	// Released key
	else if (e.type == SDL_KEYUP)
	{
		unsigned long key = e.key.keysym.sym;

		// Check if it exists
		if (keyDown.count(key))
		{
			keyDown[key] = false;
		}
		else
		{
			Log::Write("Could not find key!!");
		}
	}
	// Moved mouse
	else if (e.type == SDL_MOUSEMOTION)
	{
		UpdateMousePosition();
	}
	// Pressed mouse button
	else if (e.type == SDL_MOUSEBUTTONDOWN)
	{
		if (e.button.button == SDL_BUTTON_LEFT)
			mouseButtonDown[0] = true;
		if (e.button.button == SDL_BUTTON_RIGHT)
			mouseButtonDown[1] = true;
	}
	// Released mouse button
	else if(e.type == SDL_MOUSEBUTTONUP)
	{
		if (e.button.button == SDL_BUTTON_LEFT)
			mouseButtonDown[0] = false;
		if (e.button.button == SDL_BUTTON_RIGHT)
			mouseButtonDown[1] = false;
	}
}

void Input::SetLockMouse(bool lock)
{
	Input::lockMouse = lock;

	SDL_ShowCursor(!lock);
}

bool Input::IsKeyDown(IK key)
{
	unsigned int sdlKey = keyToSdl.at(key);

	return keyDown.at(sdlKey);
}

bool Input::IsKeyJustPressed(IK key)
{
	unsigned int sdlKey = keyToSdl.at(key);

	return keyDown.at(sdlKey) && !lastKeyDown.at(sdlKey);
}

bool Input::IsMouseDown(int mouseButtonIndex)
{
	if (mouseButtonIndex < 0 || mouseButtonIndex > maxMouseButtons)
	{
		Log::Write("Mouse button index is out of range!!!");
		return false;
	}

	return mouseButtonDown[mouseButtonIndex];
}

bool Input::IsMouseJustPressed(int mouseButtonIndex)
{
	if (mouseButtonIndex < 0 || mouseButtonIndex > maxMouseButtons)
	{
		Log::Write("Mouse button index is out of range!!!");
		return false;
	}

	return mouseButtonDown[mouseButtonIndex] && 
		!lastMouseButtonDown[mouseButtonIndex];
}

const glm::vec2& Input::GetMousePosition() const
{
	return mousePosition;
}

const glm::vec2& Input::GetMouseDelta() const
{
	return mouseDelta;
}