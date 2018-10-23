#pragma once

#include "AbstractScene.h"

namespace Castlevania
{
	class GameplayScene : public AbstractScene
	{
	public:
		GameplayScene(SceneManager &sceneManager);

		void LoadContent() override;
		void Update(float deltaTime) override;
		void Draw(GameTime gameTime) override;
	};
}