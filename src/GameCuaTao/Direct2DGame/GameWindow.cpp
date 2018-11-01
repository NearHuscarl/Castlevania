#include "GameWindow.h"
#include "Game.h"
#include "Utilities/FileLogger.h"

HINSTANCE GameWindow::instance = HINSTANCE{ nullptr };

GameWindow::GameWindow(Game &game) : game{ game }
{
	instance = GetModuleHandle(nullptr);

	width = GraphicsDeviceManager::DefaultBackbufferWidth;
	height = GraphicsDeviceManager::DefaultBackbufferHeight;

	// TODO: refactor
	windowClassName = L"SampleWindow";
	windowTitle = L"02 - Sprite animation";
}

Rect GameWindow::GetClientBound()
{
	auto position = POINT{};
	ClientToScreen(handle, &position);

	return Rect{ position.x, position.y, width, height };
}

Rect GameWindow::GetWindowBound()
{
	return windowBound;
}

HWND GameWindow::GetHandle()
{
	return handle;
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
	windowClassEx.hInstance = instance;

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

	handle = CreateWindow(
		windowClassName,
		windowTitle,
		WS_OVERLAPPEDWINDOW, // WS_EX_TOPMOST | WS_VISIBLE | WS_POPUP,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		windowBound.Width(),
		windowBound.Height(),
		nullptr,
		nullptr,
		instance,
		nullptr);

	if (!handle)
	{
		// TODO: use string template to populate error code
		auto ErrCode = GetLastError();
		FileLogger::GetInstance().Error("CreateWindow failed");
		handle = nullptr;
	}
	else
	{
		ShowWindow(handle, SW_SHOWNORMAL);
		UpdateWindow(handle);
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