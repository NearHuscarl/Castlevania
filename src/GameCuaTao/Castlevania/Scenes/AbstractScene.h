#pragma once

#include "Direct2DGame/GameTime.h"

namespace Castlevania
{
	class SceneManager;

	class AbstractScene
	{
	public:
		AbstractScene(SceneManager &sceneManager);

		virtual void LoadContent() = 0;
		virtual void Update(float deltaTime) = 0;
		virtual void Draw(GameTime gameTime) = 0;

		virtual ~AbstractScene();

	protected:
		SceneManager &sceneManager;
	};
}