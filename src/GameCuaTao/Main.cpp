#include "MarioSample/MarioSampleGame.h"
#include "Castlevania/CastlevaniaGame.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	MarioSample::MarioSampleGame{}.Run();
	//Castlevania::CastlevaniaGame{}.Run();
}