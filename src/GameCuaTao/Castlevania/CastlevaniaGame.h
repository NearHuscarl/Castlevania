#pragma once

#include "Direct2DGame/Game.h"
#include "Scenes/SceneManager.h"

namespace Castlevania
{
	class CastlevaniaGame : public Game
	{
	public:
		CastlevaniaGame();

		void Initialize() override;
		void LoadContent() override;
		void Update(GameTime gameTime) override;
		void Draw(GameTime gameTime) override;

	private:
		std::unique_ptr<SpriteBatch> spriteBatch;
		std::unique_ptr<SceneManager> sceneManager;
	};
}