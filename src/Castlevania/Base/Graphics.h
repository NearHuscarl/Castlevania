#pragma once

#include "../Utilities/DirectX.h"


class Graphics
{
public:
	Graphics() {};
	Graphics(HINSTANCE hInstance, int nCmdShow, int ScreenWidth, int ScreenHeight);
	
	void Initialize();
	HWND GetWindowHandler();

	GDevicePtr GetDirect3DDevice() { return d3ddv; }
	GSurfacePtr GetBackBuffer() { return backBuffer; }
	GSpritePtr GetSpriteHandler() { return spriteHandler; }

	D3DCOLOR GetTransparentColor() { return transparentColor; }
	void SetTransparentColor(D3DCOLOR color) { transparentColor = color; }

	~Graphics();

private:

	HINSTANCE hInstance;
	int nCmdShow;

	int ScreenWidth;
	int ScreenHeight;

	int frameRate;

	HWND hWnd;								// Window handle

	GDevicePtr d3ddv = nullptr;				// Direct3D device object
	GSurfacePtr backBuffer = nullptr;
	GSpritePtr spriteHandler = nullptr;		// Sprite helper library to help us draw 2D image on the screen 

	D3DCOLOR transparentColor;

	void InitializeDevices();
	void InitWindow();

	static LRESULT CALLBACK WinProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
};