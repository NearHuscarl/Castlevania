#pragma once

#include "Direct2DGame/IUpdateable.h"

namespace Castlevania
{
	class MovementSystem : public IUpdateable
	{
	public:
		void Update(GameTime gameTime) override;
	};
}