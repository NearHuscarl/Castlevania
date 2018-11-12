#pragma once

#include "../GameObject.h"

namespace Castlevania
{
	class Bat : public GameObject
	{
	public:
		Bat();
		void LoadContent(ContentManager &content) override;
		void Draw(SpriteExtensions &spriteBatch) override;
	};
}