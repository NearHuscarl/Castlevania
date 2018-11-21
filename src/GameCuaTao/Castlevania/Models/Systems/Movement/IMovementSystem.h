#pragma once

#include "Direct2DGame/Base/Vector2.h"
#include "../IReceiver.h"

namespace Castlevania
{
	constexpr auto GRAVITY = 18.0f;
	
	class IMovementSystem : public IReceiver
	{
	public:
		virtual Vector2 GetDistance() = 0;
		virtual void SetDistance(Vector2 distance) = 0;
		virtual void Update(float deltaTime) = 0;
		virtual ~IMovementSystem() {}
	};
}