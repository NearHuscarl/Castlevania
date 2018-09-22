#pragma once
#include "Command.h"

class JumpCommand : public Command
{
	void Jump();
public:
	virtual void execute() { Jump(); }
};