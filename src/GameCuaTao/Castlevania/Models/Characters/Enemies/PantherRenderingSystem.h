#pragma once

#include "Direct2DGame/Extensions/Animations/AnimatedSprite.h"
#include "Panther.h"
#include "../../Systems/Rendering/RenderingSystem.h"

namespace Castlevania
{
	class PantherRenderingSystem : public RenderingSystem
	{
	public:
		PantherRenderingSystem(Panther &parent, std::string animationPath, std::unique_ptr<IEffect> effect);

		Sprite &GetSprite() override;
		GameObject &GetParent() override;

		virtual void Receive(int message) override;

		void LoadContent(ContentManager &content) override;
		void Update(GameTime gameTime) override;
		void Draw(SpriteExtensions &spriteBatch) override;

	private:
		Panther &parent;
		std::unique_ptr<AnimatedSprite> sprite;
		std::unique_ptr<IEffect> hitEffect;
		std::string animationPath;

		void OnMoveStateChanged();
		void OnStateChanged();
	};
}
