#pragma once

#include <memory>
#include "Direct2DGame/Content/ContentManager.h"
#include "AbstractScene.h"
#include "Scene.h"

namespace Castlevania
{
	class SceneManager
	{
	public:
		SceneManager(std::shared_ptr<ContentManager> content);

		AbstractScene *GetCurrentScene();
		void NextScene(Scene scene);

		void Update(float deltaTime);
		void Draw(SpriteBatch &spriteBatch);

	private:
		std::unique_ptr<AbstractScene> currentScene;
		std::shared_ptr<ContentManager> content;

		std::unique_ptr<AbstractScene> GetScene(Scene scene);
	};
}