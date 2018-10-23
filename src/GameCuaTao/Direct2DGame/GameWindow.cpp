#include "GameWindow.h"
#include "Utilities/FileLogger.h"

GameWindow::GameWindow()
{
	this->hInstance = GetModuleHandle(nullptr);
	// TODO: refactor
	windowClassName = L"SampleWindow";
	windowTitle = L"02 - Sprite animation";
}

void GameWindow::Create()
{
	auto WINDOW_CLASS_NAME = windowClassName;
	auto MAIN_WINDOW_TITLE = windowTitle;

	auto windowClassEx = WNDCLASSEX{};
	windowClassEx.cbSize = sizeof(WNDCLASSEX);

	windowClassEx.style = CS_HREDRAW | CS_VREDRAW;
	windowClassEx.hInstance = hInstance;

	windowClassEx.lpfnWndProc = (WNDPROC)WinProc;
	windowClassEx.cbClsExtra = 0;
	windowClassEx.cbWndExtra = 0;
	windowClassEx.hIcon = nullptr;
	windowClassEx.hCursor = LoadCursor(nullptr, IDC_ARROW);
	windowClassEx.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	windowClassEx.lpszMenuName = nullptr;
	windowClassEx.lpszClassName = WINDOW_CLASS_NAME;
	windowClassEx.hIconSm = nullptr;

	RegisterClassEx(&windowClassEx);

	hWnd = CreateWindow(
		WINDOW_CLASS_NAME,
		MAIN_WINDOW_TITLE,
		WS_OVERLAPPEDWINDOW, // WS_EX_TOPMOST | WS_VISIBLE | WS_POPUP,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		width,
		height,
		nullptr,
		nullptr,
		hInstance,
		nullptr);

	if (!hWnd)
	{
		// TODO: use string template to populate error code
		auto ErrCode = GetLastError();
		FileLogger::GetInstance().Error("CreateWindow failed");
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

void GameWindow::Width(int width)
{
	this->width = width;
}

void GameWindow::Height(int height)
{
	this->height = height;
}

int GameWindow::Width()
{
	return width;
}

int GameWindow::Height()
{
	return height;
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