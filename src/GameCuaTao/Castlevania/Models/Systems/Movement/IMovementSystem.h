#pragma once

#include "Direct2DGame/Base/Vector2.h"
#include "Direct2DGame/GameTime.h"
#include "../IReceiver.h"

namespace Castlevania
{
	class IMovementSystem : public IReceiver
	{
	public:
		virtual void Enabled(bool value) = 0;
		virtual bool Enabled() = 0;

		virtual Vector2 GetDistance() = 0;
		virtual void SetDistance(Vector2 distance) = 0;

		virtual void Update(GameTime gameTime) = 0;
		virtual ~IMovementSystem() {}
	};
}