#include "../Commands/JumpCommand.h"
#include "../Commands/WalkLeftCommand.h"
#include "../Commands/WalkRightCommand.h"

#include "InputHandler.h"
#include <conio.h>

#define KB_UP 72
#define KB_LEFT 75
#define KB_RIGHT 77

InputHandler::InputHandler()
{
	upButton = new JumpCommand();
	leftButton = new WalkLeftCommand();
	rightButton = new WalkRightCommand();
}

void InputHandler::GetInput()
{
	KB_code = _getch();
}

bool InputHandler::IsPressed(int key)
{
	if (KB_code == key)
		return true;

	return false;
}

void InputHandler::HandleInput()
{
	if (IsPressed(KB_UP)) upButton->execute();
	else if (IsPressed(KB_LEFT)) leftButton->execute();
	else if (IsPressed(KB_RIGHT)) rightButton->execute();
}

InputHandler::~InputHandler()
{
	delete upButton;
	delete rightButton;
	delete leftButton;
}