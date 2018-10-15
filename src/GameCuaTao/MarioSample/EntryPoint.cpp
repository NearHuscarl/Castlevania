#include "EntryPoint.h"

DemoGame *EntryPoint::game = nullptr;


void EntryPoint::Init(HINSTANCE hInstance)
{
	EntryPoint::game = new DemoGame(hInstance);
}

DemoGame *EntryPoint::Game()
{
	return EntryPoint::game;
}