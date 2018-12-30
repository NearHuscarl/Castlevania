#include "ControlSystem.h"

using namespace Castlevania;

void ControlSystem::Enabled(bool value)
{
	enabled = value;
}

bool ControlSystem::Enabled()
{
	return enabled;
}
