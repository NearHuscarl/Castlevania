#pragma once
#include "Command.h"

class WalkRightCommand : public Command
{
	void Walk();
public:
	virtual void execute() { Walk(); }
};