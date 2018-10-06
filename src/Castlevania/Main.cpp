#include "EntryPoint.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	EntryPoint::Init(hInstance, nCmdShow);
	EntryPoint::Game()->Initialize();
	EntryPoint::Game()->Run();

	return 0;
}