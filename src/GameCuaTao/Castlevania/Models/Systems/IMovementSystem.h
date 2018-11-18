#pragma once

#include "Direct2DGame/Base/Vector2.h"

namespace Castlevania
{
	constexpr auto GRAVITY = 18.0f;
	
	class IMovementSystem
	{
	public:
		virtual Vector2 GetDistance() = 0;
		virtual void Update(float deltaTime) = 0;
	};
}