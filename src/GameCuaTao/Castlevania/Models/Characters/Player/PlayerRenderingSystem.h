#pragma once

#include "Direct2DGame/Extensions/Animations/AnimatedSprite.h"
#include "Player.h"
#include "../../Systems/Rendering/RenderingSystem.h"

namespace Castlevania
{
	class PlayerRenderingSystem : public RenderingSystem
	{
	public:
		PlayerRenderingSystem(Player &parent, std::string animationPath);

		Sprite &GetSprite() override;
		GameObject &GetParent() override;

		virtual void Receive(int message) override;

		void LoadContent(ContentManager &content) override;
		void Update(GameTime gameTime) override;
		void Draw(SpriteExtensions &spriteBatch) override;

	private:
		Player &parent;
		std::unique_ptr<AnimatedSprite> sprite;
		std::string animationPath;
		bool drawInvisibleEffect;

		void UpdateNormalState();
		void UpdateInvisibleRendering();
		void PlayAnimation(std::string name);

		void OnStateChanged() override;
		void OnMoveStateChanged() override;
		void OnAttackStateChanged();
	};
}
