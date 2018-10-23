#pragma once

#include "AbstractScene.h"

namespace Castlevania
{
	class IntroScene : public AbstractScene
	{
	public:
		void LoadContent(ContentManager &content) override;
		void Update(float deltaTime) override;
		void Draw(SpriteBatch &spriteBatch) override;
	};
}