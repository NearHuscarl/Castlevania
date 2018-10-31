#include "GameWindow.h"
#include "Game.h"
#include "Utilities/FileLogger.h"

GameWindow::GameWindow(Game &game) : game(game)
{
	hInstance = GetModuleHandle(nullptr);

	width = GraphicsDeviceManager::DefaultBackbufferWidth;
	height = GraphicsDeviceManager::DefaultBackbufferHeight;

	// TODO: refactor
	windowClassName = L"SampleWindow";
	windowTitle = L"02 - Sprite animation";
}

Rect GameWindow::GetClientBound()
{
	return Rect{ 0, 0, width, height }; // TODO: take account of position
}

Rect GameWindow::GetWindowBound()
{
	return windowBound;
}

HWND GameWindow::GetHandle()
{
	return hWnd;
}

void GameWindow::Create()
{
	width = game.GetGraphicsDeviceManager().GetBackBufferWidth();
	height = game.GetGraphicsDeviceManager().GetBackBufferHeight();

	// AdjustWindowRectEx() is used to calculate the whole window size from client size
	// Only use this BEFORE creating window, there's no guarantee that it will produce
	// an accurate set of window dimensions for an existing window
	// https://stackoverflow.com/questions/140347/win32-mfc-get-window-rect-from-client-rect
	windowBound = GetClientBound();
	AdjustWindowRectEx(&windowBound, WS_OVERLAPPEDWINDOW, false, 0);

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
	windowClassEx.lpszClassName = windowClassName;
	windowClassEx.hIconSm = nullptr;

	RegisterClassEx(&windowClassEx);

	hWnd = CreateWindow(
		windowClassName,
		windowTitle,
		WS_OVERLAPPEDWINDOW, // WS_EX_TOPMOST | WS_VISIBLE | WS_POPUP,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		windowBound.Width(),
		windowBound.Height(),
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