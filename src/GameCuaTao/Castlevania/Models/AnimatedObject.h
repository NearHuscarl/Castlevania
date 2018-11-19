#pragma once

#include "Direct2DGame/Extensions/Animations/AnimatedSprite.h"
#include "GameObject.h"
#include "Systems/IAnimationRenderingSystem.h"

namespace Castlevania
{
	enum class Facing
	{
		Right,
		Left,
		None,
	};

	class AnimatedObject : public GameObject
	{
	public:
		AnimatedObject();
		AnimatedObject(EntityType type);

		Facing GetFacing();

		RectF GetFrameRect();
		RectF GetBoundingBox() override;
		AnimatedSprite &GetSprite();

		template<typename T>
		void AttachRenderer(std::unique_ptr<T> system);

		void LoadContent(ContentManager &content) override;
		void Update(float deltaTime, ObjectCollection *objectCollection = nullptr) override;
		void Draw(SpriteExtensions &spriteBatch) override;

		~AnimatedObject();

	protected:
		Facing facing;

	private:
		std::unique_ptr<IAnimationRenderingSystem> renderingSystem;
	};
}