#include "GameWindow.h"
#include "Game.h"
#include "Utilities/FileLogger.h"
#include "Utilities/WinHelper.h"

HINSTANCE GameWindow::instance = HINSTANCE{ nullptr };

GameWindow::GameWindow(Game &game) : game{ game }
{
	instance = GetModuleHandle(nullptr);

	width = GraphicsDeviceManager::DefaultBackbufferWidth;
	height = GraphicsDeviceManager::DefaultBackbufferHeight;

	windowClassName = "Direct2DGame";
	windowTitle = "Direct2D Game";
	icon = "Icon.ico";
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

void GameWindow::SetTitle(std::string title)
{
	windowTitle = title;
	windowClassName = windowTitle;
}

void GameWindow::SetIcon(std::string iconPath)
{
	icon = iconPath;
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
	auto className = WinHelper::s2ws(windowClassName);
	auto title = WinHelper::s2ws(windowTitle);
	auto iconPath = WinHelper::s2ws(icon);

	windowClassEx.cbSize = sizeof(WNDCLASSEX);

	windowClassEx.style = CS_HREDRAW | CS_VREDRAW;
	windowClassEx.hInstance = instance;

	windowClassEx.lpfnWndProc = (WNDPROC)WinProc;
	windowClassEx.cbClsExtra = 0;
	windowClassEx.cbWndExtra = 0;
	windowClassEx.hIcon = (HICON)LoadImage( // returns a HANDLE so we have to cast to HICON
		NULL,             // hInstance must be NULL when loading from a file
		iconPath.c_str(), // the icon file name
		IMAGE_ICON,       // specifies that the file is an icon
		0,                // width of the image (we'll specify default later on)
		0,                // height of the image
		LR_LOADFROMFILE | // we want to load a file (as opposed to a resource)
		LR_DEFAULTSIZE |  // default metrics based on the type (IMAGE_ICON, 32x32)
		LR_SHARED         // let the system release the handle when it's no longer used
	);
	windowClassEx.hCursor = LoadCursor(nullptr, IDC_ARROW);
	windowClassEx.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	windowClassEx.lpszMenuName = nullptr;
	windowClassEx.lpszClassName = className.c_str();
	windowClassEx.hIconSm = nullptr;

	RegisterClassEx(&windowClassEx);

	handle = CreateWindow(
		className.c_str(),
		title.c_str(),
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
		FileLogger::GetInstance().Error("{}(): CreateWindow failed with error code {}", __FUNCTION__, GetLastError());
		handle = nullptr;
	}
	else
	{
		ShowWindow(handle, SW_SHOWNORMAL);
		UpdateWindow(handle);
	}
}

LRESULT CALLBACK GameWindow::WinProc(HWND handle, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
		case WM_DESTROY:
			PostQuitMessage(0);
			break;
		default:
			return DefWindowProc(handle, message, wParam, lParam);
	}

	return 0;
}