#pragma once

#include <windows.h>
#include "Game.h"
#include "Models/Mario.h"

class DemoGame : public Game
{
public:
	DemoGame(HINSTANCE hInstance, int nCmdShow);
	Mario *mario;

	void Initialize() override;
	void LoadResources() override;
	void Update(unsigned long dt) override;
	void Draw() override;
};