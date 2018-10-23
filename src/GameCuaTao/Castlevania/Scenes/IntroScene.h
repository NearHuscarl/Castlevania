#pragma once

#include "AbstractScene.h"

namespace Castlevania
{
	class IntroScene : public AbstractScene
	{
	public:
		IntroScene(SceneManager &sceneManager);

		void LoadContent() override;
		void Update(float deltaTime) override;
		void Draw(GameTime gameTime) override;
	};
}