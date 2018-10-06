#include "EntryPoint.h"

DemoGame *EntryPoint::game = NULL;


void EntryPoint::Init(HINSTANCE hInstance, int nCmdShow)
{
	EntryPoint::game = new DemoGame(hInstance, nCmdShow);
}

DemoGame *EntryPoint::Game()
{
	return EntryPoint::game;
}