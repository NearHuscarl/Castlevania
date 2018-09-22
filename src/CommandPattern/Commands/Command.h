#pragma once
class Command
{
public:
	virtual ~Command() {}
	virtual void execute() = 0;
};