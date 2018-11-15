#pragma once

#include "Direct2DGame/IUpdateable.h"

namespace Castlevania
{
	class PlayerControlSystem : public IUpdateable
	{
	public:
		void Update(GameTime gameTime) override;
	};
}