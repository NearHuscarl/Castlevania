#pragma once

#include <Windows.h>
#include <string>
#include "Base/Rect.h"

class Game;

class GameWindow
{
public:
	GameWindow(Game &game);

	HWND GetHandle();
	Rect GetClientBound();
	Rect GetWindowBound();
	void SetTitle(std::string title);
	void SetIcon(std::string iconPath);

	void Create();

private:
	Game &game;

	static HINSTANCE instance;
	HWND handle;

	int width;
	int height;
	Rect windowBound;

	std::string windowClassName;
	std::string windowTitle;
	std::string icon;

	static LRESULT CALLBACK WinProc(HWND handle, UINT message, WPARAM wParam, LPARAM lParam);
};