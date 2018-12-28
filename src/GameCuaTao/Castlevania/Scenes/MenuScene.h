#pragma once

#include <memory>
#include <string>
#include "Direct2DGame/Graphics/SpriteFont.h"
#include "Direct2DGame/Extensions/Animations/AnimatedSprite.h"
#include "Direct2DGame/Utilities/Stopwatch.h"
#include "AbstractScene.h"

namespace Castlevania
{
	class MenuScene : public AbstractScene
	{
	public:
		MenuScene(SceneManager &sceneManager);

		void LoadContent() override;
		void Update(GameTime gameTime) override;
		void Draw(GameTime gameTime) override;

	private:
		enum class State;

		State currentState;
		std::shared_ptr<Texture> background;
		std::shared_ptr<SpriteFont> menuFont;
		std::unique_ptr<AnimatedSprite> menuBatSprite;

		std::string startGameText;
		std::string copyrightText;

		Vector2 menuBatPosition;
		Vector2 startGameTextPosition;
		Vector2 copyrightTextPosition;

		Stopwatch transitionTimer;
	};
}