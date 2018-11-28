#pragma once

#include "Direct2DGame/Extensions/Animations/AnimatedSprite.h"
#include "../Systems/Rendering/IRenderingSystem.h"

namespace Castlevania
{
	class Whip;

	class WhipRenderingSystem : public IRenderingSystem
	{
	public:
		WhipRenderingSystem(Whip &parent, std::string spriteConfigPath);

		RectF GetBoundingBox() override;
		AnimatedSprite &GetSprite() override;

		virtual void Receive(int message) override;

		void LoadContent(ContentManager &content) override;
		void Update(GameTime gameTime) override;
		void Draw(SpriteExtensions &spriteBatch) override;

	protected:
		Whip &parent;
		std::unique_ptr<AnimatedSprite> sprite;
		std::string spriteConfigPath;
		
		virtual void OnEnabledChanged();

		void UpdatePositionRelativeToPlayer();
	};
}
