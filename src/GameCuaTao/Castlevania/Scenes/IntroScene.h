#pragma once

#include <memory>
#include "Direct2DGame/Graphics/Texture.h"
#include "AbstractScene.h"
#include "../Models/Characters/Simon.h"
#include "../Models/Characters/Bat.h"

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
		std::unique_ptr<Bat> bat1; // left-side bat
		std::unique_ptr<Bat> bat2; // right-side bat

		Vector2 startPosition;
		Vector2 gatePosition;
	};
}