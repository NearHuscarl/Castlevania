#pragma once

#include "Direct2DGame/Base/Vector2.h"

namespace Castlevania
{
	class IMovementSystem
	{
	public:
		virtual Vector2 GetDistance() = 0;
		virtual void Update() = 0;
	};
}