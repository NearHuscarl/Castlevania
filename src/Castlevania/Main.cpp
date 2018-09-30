#include "EntryPoint.h"


static int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	EntryPoint::Init(new DemoGame(hInstance, nCmdShow));

	EntryPoint::Game()->Initialize();
	EntryPoint::Game()->Run();

	return 0;
}