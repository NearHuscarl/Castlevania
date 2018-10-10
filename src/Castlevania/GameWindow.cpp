#include "GameWindow.h"
#include "Utilities/FileLogger.h"
#include "Utilities/WinHelper.h"

GameWindow::GameWindow()
{
}

GameWindow::GameWindow(HINSTANCE hInstance)
{
	this->hInstance = hInstance;
	// TODO: refactor
	windowClassName = L"SampleWindow";
	windowTitle = L"02 - Sprite animation";
}

void GameWindow::Create()
{
	auto WINDOW_CLASS_NAME = windowClassName;
	auto MAIN_WINDOW_TITLE = windowTitle;

	WNDCLASSEX wc;
	wc.cbSize = sizeof(WNDCLASSEX);

	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.hInstance = hInstance;

	wc.lpfnWndProc = (WNDPROC)WinProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hIcon = nullptr;
	wc.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wc.lpszMenuName = nullptr;
	wc.lpszClassName = WINDOW_CLASS_NAME;
	wc.hIconSm = nullptr;

	RegisterClassEx(&wc);

	hWnd = CreateWindow(
		WINDOW_CLASS_NAME,
		MAIN_WINDOW_TITLE,
		WS_OVERLAPPEDWINDOW, // WS_EX_TOPMOST | WS_VISIBLE | WS_POPUP,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		screenWidth,
		screenHeight,
		nullptr,
		nullptr,
		hInstance,
		nullptr);

	if (!hWnd)
	{
		FileLogger::GetInstance()->Error("CreateWindow failed");
		DWORD ErrCode = GetLastError();
		hWnd = nullptr;
	}
	else
	{
		ShowWindow(hWnd, SW_SHOWNORMAL);
		UpdateWindow(hWnd);
	}
}

HWND GameWindow::GetHandle()
{
	return hWnd;
}

void GameWindow::SetScreenWidth(int width)
{
	screenWidth = width;
}

void GameWindow::SetScreenHeight(int height)
{
	screenHeight = height;
}

LRESULT CALLBACK GameWindow::WinProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
		case WM_DESTROY:
			PostQuitMessage(0);
			break;
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
	}

	return 0;
}