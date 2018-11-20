#pragma once

#include "ISpriteRenderingSystem.h"

namespace Castlevania
{
	class SpriteRenderingSystem : public ISpriteRenderingSystem
	{
	public:
		SpriteRenderingSystem(StaticObject &parent, std::string spritePath);

		RectF GetBoundingBox() override;
		Sprite &GetSprite() override;

		void LoadContent(ContentManager &content) override;
		void Update(float deltaTime) override;
		void Draw(SpriteExtensions &spriteBatch) override;

	protected:
		StaticObject &parent;
		std::unique_ptr<Sprite> sprite;
		std::string spritePath;
	};
}
