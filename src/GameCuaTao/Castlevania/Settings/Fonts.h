#pragma once

#include "Direct2DGame/Graphics/SpriteFont.h"
#include "Direct2DGame/Content/ContentManager.h"

namespace Castlevania
{
	// Static storage of SpriteFont objects for use throughout the game.
	class Fonts
	{
	public:
		static SpriteFont Main;
		static void LoadContent(ContentManager &content);
	};
}