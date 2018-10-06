#pragma once

#include "DemoGame.h"


/// Entry point of the whole application
class EntryPoint
{
public:
	static void Init(HINSTANCE hInstance, int nCmdShow);
	static DemoGame *Game();

private:
	static DemoGame *game;
};