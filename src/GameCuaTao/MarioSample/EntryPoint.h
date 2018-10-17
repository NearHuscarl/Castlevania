#pragma once

#include "DemoGame.h"

// Entry point of the whole application
class EntryPoint
{
public:
	static void Init(HINSTANCE hInstance);
	static DemoGame &Game();

private:
	static std::unique_ptr<DemoGame> game;
};