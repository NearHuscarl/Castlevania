#pragma once

#include "Direct2DGame/Extensions/Animations/AnimatedSprite.h"
#include "Player.h"

namespace Castlevania
{
	class PlayerRenderingSystem : public IRenderingSystem
	{
	public:
		PlayerRenderingSystem(Player &parent, std::string spriteConfigPath);

		RectF GetBoundingBox() override;
		Sprite &GetSprite() override;

		virtual void Receive(int message) override;

		void LoadContent(ContentManager &content) override;
		void Update(float deltaTime) override;
		void Draw(SpriteExtensions &spriteBatch) override;

	private:
		Player &parent;
		std::unique_ptr<AnimatedSprite> sprite;
		std::string spriteConfigPath;

		void OnMoveStateChanged();
		void OnAttackStateChanged();
	};
}
