#pragma once

#include "../Utilities/DirectX.h"


class Graphics
{
public:
	Graphics(HINSTANCE hInstance, int nCmdShow, int ScreenWidth, int ScreenHeight);
	
	void InitializeDevices();
	void InitWindow();
	HWND GetWindowHandler();

	GDevicePtr GetDirect3DDevice() { return d3ddv; }
	GSurfacePtr GetBackBuffer() { return backBuffer; }
	GSpritePtr GetSpriteHandler() { return spriteHandler; }

	~Graphics();

private:

	HINSTANCE hInstance;
	int nCmdShow;

	int ScreenWidth;
	int ScreenHeight;

	HWND hWnd;								// Window handle

	GDevicePtr d3ddv = NULL;				// Direct3D device object
	GSurfacePtr backBuffer = NULL;
	GSpritePtr spriteHandler = NULL;		// Sprite helper library to help us draw 2D image on the screen 

	static LRESULT CALLBACK WinProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
};