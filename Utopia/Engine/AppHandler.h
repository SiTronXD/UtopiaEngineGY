#pragma once


class AppHandler
{
private:
	static bool quit;

	static int screenWidth;
	static int screenHeight;

public:
	AppHandler();
	virtual ~AppHandler();

	static void Quit();
	static void SetScreenWidthGetter(int width);
	static void SetScreenHeightGetter(int height);

	static bool ShouldQuit();
	static int GetScreenWidth();
	static int GetScreenHeight();
};