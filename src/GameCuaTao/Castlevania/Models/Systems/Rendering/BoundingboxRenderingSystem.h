#pragma once

#include "Direct2DGame/Extensions/Sprites/Sprite.h"
#include "RenderingSystem.h"

namespace Castlevania
{
	class BoundingBoxRenderingSystem : public RenderingSystem
	{
	public:
		BoundingBoxRenderingSystem(GameObject &parent, RectF boundingBox);

		Sprite &GetSprite() override;
		GameObject &GetParent() override;

		void LoadContent(ContentManager &content) override;
		void Draw(SpriteExtensions &spriteBatch) override;

	protected:
		GameObject &parent;
		std::unique_ptr<Sprite> sprite;
		RectF boundingBox;
	};
}
