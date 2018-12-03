#pragma once

#include "Direct2DGame/GameTime.h"
#include "Direct2DGame/Content/ContentManager.h"
#include "Direct2DGame/Extensions/Sprites/SpriteExtensions.h"
#include "../IReceiver.h"

namespace Castlevania
{
	class GameObject;

	class IRenderingSystem : public IReceiver
	{
	public:
		virtual Sprite &GetSprite() = 0;
		
		virtual void LoadContent(ContentManager &content) = 0;
		virtual void Update(GameTime gameTime) = 0;
		virtual void Draw(SpriteExtensions &spriteBatch) = 0;

		virtual ~IRenderingSystem() {}
	};
}
