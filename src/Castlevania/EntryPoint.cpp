#include "EntryPoint.h"

DemoGame *EntryPoint::game = NULL;


void EntryPoint::Init(DemoGame *game)
{
	EntryPoint::game = game;
}

DemoGame *EntryPoint::Game()
{
	return EntryPoint::game;
}