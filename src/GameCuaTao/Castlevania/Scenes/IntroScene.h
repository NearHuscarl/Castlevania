#pragma once

#include <memory>
#include "Direct2DGame/Graphics/Texture.h"
#include "AbstractScene.h"
#include "../Models/Simon.h"

namespace Castlevania
{
	class IntroScene : public AbstractScene
	{
	public:
		IntroScene(SceneManager &sceneManager);

		void LoadContent() override;
		void Update(float deltaTime) override;
		void Draw(GameTime gameTime) override;

	private:
		std::shared_ptr<Texture> background;
		std::unique_ptr<Simon> simon;

		Vector2 startPosition;
		Vector2 gatePosition;
	};
}