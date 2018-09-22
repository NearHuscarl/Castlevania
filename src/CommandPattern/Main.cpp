// Source code example for Command pattern
// http://gameprogrammingpatterns.com/command.html

#include <iostream>
#include <conio.h>
#include "Models/InputHandler.h"

int main()
{
	InputHandler inputHandler;

	std::cout << "Select action using (UP|LEFT|RIGHT)\n";

	while (true)
	{
		inputHandler.GetInput();
		inputHandler.HandleInput();
	}

	return 0;
}