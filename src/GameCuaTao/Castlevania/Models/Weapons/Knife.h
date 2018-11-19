#pragma once

#include "../StaticObject.h"

namespace Castlevania
{
	class Knife : public StaticObject
	{
	public:
		Knife();

		void LoadContent(ContentManager &content) override;
		void Draw(SpriteExtensions &spriteBatch) override;
	};
}