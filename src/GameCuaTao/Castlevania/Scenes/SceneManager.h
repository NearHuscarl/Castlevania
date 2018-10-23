#pragma once

#include <memory>
#include "Direct2DGame/Game.h"
#include "AbstractScene.h"
#include "Scene.h"

namespace Castlevania
{
	class SceneManager
	{
	public:
		SceneManager(Game &game);

		GraphicsDevice &GetGraphicsDevice();
		ContentManager &GetContent();
		SpriteBatch &GetSpriteBatch();

		AbstractScene *GetCurrentScene();
		void NextScene(Scene scene);

		void Update(float deltaTime);
		void Draw(GameTime gameTime);

	private:
		Game &game;

		std::unique_ptr<AbstractScene> currentScene;
		std::unique_ptr<SpriteBatch> spriteBatch;

		std::unique_ptr<AbstractScene> GetScene(Scene scene);
	};
}