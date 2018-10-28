#pragma once

#include "Direct2DGame/Game.h"
#include "Models/Mario.h"

namespace MarioSample
{
	class MarioSampleGame : public Game
	{
	public:
		MarioSampleGame();

		void Initialize() override;
		void LoadContent() override;
		void Update(GameTime gameTime) override;
		void Draw(GameTime gameTime) override;

	private:
		std::unique_ptr<SpriteBatch> spriteBatch;

		std::shared_ptr<Mario> mario;
		std::shared_ptr<SpriteFont> gameFont;
	};
}