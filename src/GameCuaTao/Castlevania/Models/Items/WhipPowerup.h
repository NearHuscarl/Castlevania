#pragma once

#include "../StaticObject.h"

namespace Castlevania
{
	class WhipPowerup : public StaticObject
	{
	public:
		WhipPowerup();

		void LoadContent(ContentManager &content) override;
		void Draw(SpriteExtensions &spriteBatch) override;
	};
}