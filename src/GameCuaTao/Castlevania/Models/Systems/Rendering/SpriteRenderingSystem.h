#pragma once

#include "Direct2DGame/Extensions/Sprites/Sprite.h"
#include "IRenderingSystem.h"

namespace Castlevania
{
	class SpriteRenderingSystem : public IRenderingSystem
	{
	public:
		SpriteRenderingSystem(GameObject &parent, std::string spritePath);

		RectF GetBoundingBox() override;
		Sprite &GetSprite() override;

		virtual void Receive(int message) override {};

		void LoadContent(ContentManager &content) override;
		void Update(float deltaTime) override;
		void Draw(SpriteExtensions &spriteBatch) override;

	protected:
		GameObject &parent;
		std::unique_ptr<Sprite> sprite;
		std::string spritePath;
	};
}
