#include "Game.h"

#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 720

Game::Game() { }

Game::~Game() { }

typedef std::chrono::high_resolution_clock Clock;
typedef std::chrono::milliseconds Milliseconds;

void Game::Run()
{
	Display display(SCREEN_WIDTH, SCREEN_HEIGHT, "Utopia Engine!!!", input);

	// AppHandler settings
	AppHandler::SetScreenWidthGetter(SCREEN_WIDTH);
	AppHandler::SetScreenHeightGetter(SCREEN_HEIGHT);

	input.SetWindow(display.GetWindow());

	GameStateManager gsm;
	gsm.SetGameState(new GYState(input));

	// Clock to calculate delta time
	Clock::time_point oldClock = Clock::now();
	//Clock::time_point oldClock;
	Milliseconds ms;

	double deltaTime = 0.0f;
	while (!display.IsClosed() && !AppHandler::ShouldQuit())
	{
		// Calculate the current delta time
		ms = std::chrono::duration_cast<Milliseconds>(Clock::now() - oldClock);
		deltaTime = (double)(ms.count() / 1000.0f);
		oldClock = Clock::now();

		// Update and draw scene
		gsm.Update(deltaTime);
		gsm.Draw();

		// Display on screen
		display.Update();

		// Fps
		Log::Write("FPS: " + std::to_string((long)(1.0f / deltaTime)));
	}
}

int Game::GetScreenWidth() { return SCREEN_WIDTH; }
int Game::GetScreenHeight() { return SCREEN_HEIGHT; }
