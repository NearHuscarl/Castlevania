#pragma once

#include <memory>
#include "Direct2DGame/Game.h"
#include "Direct2DGame/Extensions/Sprites/SpriteExtensions.h"
#include "AbstractScene.h"
#include "Scene.h"
#include "../Models/Factories/ObjectFactory.h"

namespace Castlevania
{
	class SceneManager
	{
	public:
		SceneManager(Game &game);

		AbstractScene &GetNextScene();
		GraphicsDevice &GetGraphicsDevice();
		ContentManager &GetContent();
		ObjectFactory &GetFactory();
		SpriteExtensions &GetSpriteBatch();

		void SetNextScene(Scene scene);

		void Update(GameTime gameTime);
		void Draw(GameTime gameTime);

	private:
		Game &game;
		std::unique_ptr<AbstractScene> currentScene;
		std::unique_ptr<AbstractScene> nextScene;
		std::unique_ptr<ObjectFactory> objectFactory;
		std::unique_ptr<SpriteExtensions> spriteBatch;

		std::unique_ptr<AbstractScene> ConstructScene(Scene scene);
	};
}