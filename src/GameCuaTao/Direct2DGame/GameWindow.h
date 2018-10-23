#pragma once

#include <Windows.h>
#include <string>

class GameWindow
{
public:
	GameWindow();

	void Create();
	HWND GetHandle();

	void Width(int width);
	void Height(int height);
	int Width();
	int Height();

private:
	HINSTANCE hInstance;
	HWND hWnd;

	int width = 800;
	int height = 480;

	LPCWSTR windowClassName;
	LPCWSTR windowTitle;

	static LRESULT CALLBACK WinProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
};