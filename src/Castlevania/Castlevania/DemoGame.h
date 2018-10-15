#pragma once

#include "Direct2DGame/Game.h"
#include "Models/Mario.h"

class DemoGame : public Game
{
public:
	DemoGame(HINSTANCE hInstance);
	Mario *mario;

	void Initialize() override;
	void LoadResources() override;
	void Update(unsigned long deltaTime) override;
	void Draw(SpritePtr spriteHandler) override;
};