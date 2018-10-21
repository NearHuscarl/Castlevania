#pragma once

#include "Direct2DGame/Game.h"

namespace Castlevania
{
	class CastlevaniaGame : public Game
	{
	public:
		void Initialize() override;
		void LoadResources() override;
		void Update(GameTime gameTime) override;
		void Draw(ISpriteBatch_ spriteBatch) override;
	};
}