#pragma once

#include "AbstractScene.h"

namespace Castlevania
{
	class GameplayScene : public AbstractScene
	{
	public:
		void LoadContent(ContentManager &content) override;
		void Update(float deltaTime) override;
		void Draw(SpriteBatch &spriteBatch) override;
	};
}