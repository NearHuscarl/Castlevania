#include "ControlSystem.h"

using namespace Castlevania;

void ControlSystem::Enabled(bool value)
{
	enabled = value;
}

bool Castlevania::ControlSystem::Enabled()
{
	return enabled;
}
