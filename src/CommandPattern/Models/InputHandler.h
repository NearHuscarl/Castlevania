#pragma once
#include "../Commands/Command.h"

class InputHandler
{
public:
	InputHandler();
	
	void GetInput();
	bool IsPressed(int key);
	void HandleInput();

	~InputHandler();

private:
	int KB_code = 0;

	Command* upButton = nullptr;
	Command* leftButton = nullptr;
	Command* rightButton = nullptr;
};