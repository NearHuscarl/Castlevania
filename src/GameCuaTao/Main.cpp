#include "MarioSample/MarioSampleGame.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	MarioSample::MarioSampleGame{}.Run();
}