#pragma once

#include "Base/Graphics.h"
#include "Content.h"

class Game
{
public:
	virtual void Initialize();
	virtual void LoadResources();
	virtual void Update(unsigned long deltaTime);
	virtual void Draw();

	int Run();

protected:
	Game(HINSTANCE hInstance, int nCmdShow, int screenWidth, int screenHeight);

	Content content;
	Graphics graphics;

private:
	bool isRunning;
	void Render();
};