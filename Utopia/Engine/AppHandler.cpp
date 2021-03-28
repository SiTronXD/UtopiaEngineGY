#include "AppHandler.h"

bool AppHandler::quit;
int AppHandler::screenWidth;
int AppHandler::screenHeight;

AppHandler::AppHandler()
{
	quit = false;
}

AppHandler::~AppHandler()
{
}

void AppHandler::Quit()
{
	quit = true;
}

void AppHandler::SetScreenWidthGetter(int width)
{
	screenWidth = width;
}

void AppHandler::SetScreenHeightGetter(int height)
{
	screenHeight = height;
}

bool AppHandler::ShouldQuit()
{
	return quit;
}

int AppHandler::GetScreenWidth()
{
	return screenWidth;
}

int AppHandler::GetScreenHeight()
{
	return screenHeight;
}
