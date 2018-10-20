#pragma once

#include "Direct2DGame/Game.h"
#include "Direct2DGame/Graphics/SpriteFont.h"
#include "Models/Mario.h"

namespace MarioSample
{
	class MarioSampleGame : public Game
	{
	public:
		MarioSampleGame();
		std::shared_ptr<Mario> mario;

		void Initialize() override;
		void LoadResources() override;
		void Update(unsigned long deltaTime) override;
		void Draw(ISpriteBatch_ spriteBatch) override;

	private:
		std::shared_ptr<SpriteFont> helpText;
	};
}