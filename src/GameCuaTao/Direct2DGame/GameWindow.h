#pragma once

#include <Windows.h>
#include <string>

class GameWindow
{
public:
	GameWindow();

	void Create();
	HWND GetHandle();

	void SetScreenWidth(int width);
	void SetScreenHeight(int height);

private:
	HINSTANCE hInstance;
	HWND hWnd;

	int screenWidth = 800;
	int screenHeight = 480;

	LPCWSTR windowClassName;
	LPCWSTR windowTitle;

	static LRESULT CALLBACK WinProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
};