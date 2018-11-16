#pragma once

#include <memory>
#include "Direct2DGame/Game.h"
#include "Direct2DGame/Extensions/Sprites/SpriteExtensions.h"
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
		SpriteExtensions &GetSpriteBatch();

		void SetNextScene(Scene scene);

		void Update(float deltaTime);
		void Draw(GameTime gameTime);

	private:
		Game &game;
		std::unique_ptr<AbstractScene> currentScene;
		std::unique_ptr<AbstractScene> nextScene;
		std::unique_ptr<SpriteExtensions> spriteBatch;

		std::unique_ptr<AbstractScene> ConstructScene(Scene scene);
	};
}