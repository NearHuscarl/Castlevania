#pragma once

#include "../Systems/Rendering/IAnimationRenderingSystem.h"

namespace Castlevania
{
	class Whip;

	class WhipRenderingSystem : public IAnimationRenderingSystem
	{
	public:
		WhipRenderingSystem(Whip &parent, std::string spriteConfigPath);

		RectF GetBoundingBox() override;
		AnimatedSprite &GetSprite() override;

		void LoadContent(ContentManager &content) override;
		void Update(float deltaTime) override;
		void Draw(SpriteExtensions &spriteBatch) override;

	private:
		Whip &parent;

		std::unique_ptr<AnimatedSprite> sprite;

		std::string spriteConfigPath;

		bool IsEnabledChanged();
		void OnEnabledChange();
	};
}
