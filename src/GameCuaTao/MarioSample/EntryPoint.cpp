#include "EntryPoint.h"

std::unique_ptr<DemoGame> EntryPoint::game = nullptr;

void EntryPoint::Init(HINSTANCE hInstance)
{
	EntryPoint::game = std::make_unique<DemoGame>(hInstance);
}

DemoGame &EntryPoint::Game()
{
	return *EntryPoint::game;
}