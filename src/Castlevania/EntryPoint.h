#pragma once

#include <Windows.h>
#include "DemoGame.h"

/// Entry point of the whole application
class EntryPoint
{
public:
	static void Init(DemoGame *game);
	static DemoGame *Game();

private:
	static DemoGame *game;
};