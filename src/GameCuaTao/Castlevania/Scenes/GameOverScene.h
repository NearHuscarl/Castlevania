#pragma once

#include <memory>
#include <string>
#include "Direct2DGame/Graphics/SpriteFont.h"
#include "Direct2DGame/Extensions/Animations/AnimatedSprite.h"
#include "Direct2DGame/Utilities/Stopwatch.h"
#include "AbstractScene.h"

namespace Castlevania
{
	class GameOverScene : public AbstractScene
	{
	public:
		GameOverScene(SceneManager &sceneManager);

		void LoadContent() override;
		void Update(GameTime gameTime) override;
		void Draw(GameTime gameTime) override;

	private:
		std::shared_ptr<SpriteFont> font;
		std::shared_ptr<Texture> heartTexture;
		std::string currentOption;

		Vector2 gameOverTextPosition;
		Vector2 continueTextPosition;
		Vector2 endTextPosition;

		Vector2 GetHeartPosition();
	};
}