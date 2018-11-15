#pragma once

#include "Direct2DGame/IDrawable.h"

namespace Castlevania
{
	class HudSystem : public IDrawable
	{
	public:
		void Draw(GameTime gameTime) override;
	};
}