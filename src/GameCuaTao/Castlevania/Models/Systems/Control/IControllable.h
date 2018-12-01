#pragma once

#include "Direct2DGame/Input/IController.h"
#include "../../../Models/Systems/Control/IControlSystem.h"

namespace Castlevania
{
	// Control system that can be controlled by player input device (e.g. keyboard)
	class IControllable : public IControlSystem, public IController
	{
	};
}