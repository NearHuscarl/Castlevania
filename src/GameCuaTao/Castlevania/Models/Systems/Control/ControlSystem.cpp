#include "ControlSystem.h"

using namespace Castlevania;

ControlSystem::ControlSystem()
{
	enabled = true;
}

void ControlSystem::Enabled(bool value)
{
	enabled = value;
}

bool ControlSystem::Enabled()
{
	return enabled;
}
