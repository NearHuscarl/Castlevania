#pragma once

#include "../GameObject.h"

namespace Castlevania
{
	class FirePit : public GameObject
	{
	public:
		FirePit();
		void LoadContent(ContentManager &content) override;
		void Update(float deltaTime) override;
		void Draw(SpriteExtensions &spriteBatch) override;
	};
}