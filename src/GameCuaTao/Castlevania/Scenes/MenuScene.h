#pragma once

#include "AbstractScene.h"

namespace Castlevania
{
	class MenuScene : public AbstractScene
	{
	public:
		void LoadContent(ContentManager &content) override;
		void Update(float deltaTime) override;
		void Draw(SpriteBatch &spriteBatch) override;

	private:
		
	};
}