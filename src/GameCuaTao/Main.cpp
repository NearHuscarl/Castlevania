#include "MarioSample/MarioSampleGame.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	auto Game = MarioSample::MarioSampleGame{};

	Game.Run();

	return 0;
}