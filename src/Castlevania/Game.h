#pragma once

#include "Views/Graphics.h"

class Game
{
public:
	Game(HINSTANCE hInstance, int nCmdShow, int screenWidth, int screenHeight);

	virtual void Initialize();
	virtual void LoadResources();
	virtual void Update(DWORD dt);
	virtual void Draw();

	int Run();

private:
	Graphics *graphics;
	void Render();
};