#pragma once

#include "Direct2DGame/IUpdateable.h"

namespace Castlevania
{
	class IntroControlSystem : public IUpdateable
	{
	public:
		void Update(GameTime gameTime) override;
	};
}