#pragma once

#include <memory>
#include "Direct2DGame/Content/ContentManager.h"
#include "Direct2DGame/Extensions/Sprites/SpriteExtensions.h"
#include "Direct2DGame/Extensions/Animations/AnimatedSprite.h"

namespace Castlevania
{
	class GameObject
	{
	public:
		void SetVelocity(float velocity);
		void SetRotation(float degrees);
		void SetPosition(float x, float y);
		void SetPosition(Vector2 position);

		Vector2 GetOriginPosition(); // Get the center of the object bounding box to the world
		virtual Rect GetFrameRect();
		virtual Rect GetBoundingBox();

		virtual void LoadContent(ContentManager &content);
		virtual void Update(float deltaTime);
		void UpdateDistance(float deltaTime);

		virtual void Draw(SpriteExtensions &spriteBatch);

		virtual ~GameObject();

	protected:
		Transform transform;
		Vector2 directionVec;
		float velocity;
		float speed;

		std::unique_ptr<AnimatedSprite> sprite;
	};
}