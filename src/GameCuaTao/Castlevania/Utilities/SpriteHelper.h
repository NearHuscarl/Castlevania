#pragma once

#include "Direct2DGame/Base/Color.h"
#include "Direct2DGame/Content/ContentManager.h"
#include "Direct2DGame/Extensions/RectF.h"
#include "Direct2DGame/Graphics/SpriteBatch.h"

namespace Castlevania
{
	class SpriteHelper
	{
	public:
		static void LoadContent(ContentManager &content);
		static void DrawRectangle(SpriteBatch &spriteBatch, RectF rect, Color color);

	private:
		static std::shared_ptr<Texture> boundingBoxTexture;
	};
}