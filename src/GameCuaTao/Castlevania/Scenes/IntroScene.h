#pragma once

#include <memory>
#include "Direct2DGame/Graphics/Texture.h"
#include "Direct2DGame/Utilities/Stopwatch.h"
#include "AbstractScene.h"
#include "../Models/Characters/Player/Player.h"

namespace Castlevania
{
	class IntroScene : public AbstractScene
	{
	public:
		IntroScene(SceneManager &sceneManager);

		void LoadContent() override;
		void Update(GameTime gameTime) override;
		void Draw(GameTime gameTime) override;

	private:
		std::shared_ptr<Texture> background;

		std::unique_ptr<Player> player;
		std::unique_ptr<GameObject> bat1; // left-side bat
		std::unique_ptr<GameObject> bat2; // right-side bat

		Vector2 startPosition;
		Vector2 gatePosition;
		Stopwatch transitionTimer;
	};
}