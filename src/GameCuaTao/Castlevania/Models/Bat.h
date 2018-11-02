#pragma once

#include "GameObject.h"

namespace Castlevania
{
	class Bat : public GameObject
	{
	public:
		void LoadContent(ContentManager &content) override;
		void Update(float deltaTime) override;
		void Draw(SpriteBatch &spritebatch) override;
	};
}