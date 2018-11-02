#pragma once

#include <Windows.h>
#include <string>
#include "Base/Rect.h"

class Game;

class GameWindow
{
public:
	GameWindow(Game &game);
	void Create();

	HWND GetHandle();
	Rect GetClientBound();
	Rect GetWindowBound();

private:
	Game &game;

	static HINSTANCE instance;
	HWND handle;

	int width;
	int height;
	Rect windowBound;

	LPCWSTR windowClassName;
	LPCWSTR windowTitle;

	static LRESULT CALLBACK WinProc(HWND handle, UINT message, WPARAM wParam, LPARAM lParam);
};