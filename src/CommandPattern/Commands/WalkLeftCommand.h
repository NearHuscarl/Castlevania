#pragma once
#include "Command.h"

class WalkLeftCommand : public Command
{
	void Walk();
public:
	virtual void execute() { Walk(); }
};