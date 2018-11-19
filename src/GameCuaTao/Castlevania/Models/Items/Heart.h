#pragma once

#include "../StaticObject.h"

namespace Castlevania
{
	class Heart : public StaticObject
	{
	public:
		Heart();

		void LoadContent(ContentManager &content) override;
		void Draw(SpriteExtensions &spriteBatch) override;
	};
}