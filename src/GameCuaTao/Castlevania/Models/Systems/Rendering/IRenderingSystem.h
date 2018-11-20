#pragma once

#include "Direct2DGame/Content/ContentManager.h"
#include "Direct2DGame/Extensions/Sprites/SpriteExtensions.h"

namespace Castlevania
{
	class GameObject;

	class IRenderingSystem
	{
	public:
		virtual RectF GetBoundingBox() = 0;

		virtual void LoadContent(ContentManager &content) = 0;
		virtual void Update(float deltaTime) = 0;
		virtual void Draw(SpriteExtensions &spriteBatch) = 0;
		virtual ~IRenderingSystem() {}
	};
}
