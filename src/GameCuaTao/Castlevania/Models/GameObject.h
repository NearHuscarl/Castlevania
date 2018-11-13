#pragma once

#include <memory>
#include "Direct2DGame/Content/ContentManager.h"
#include "Direct2DGame/Extensions/Sprites/SpriteExtensions.h"
#include "Direct2DGame/Extensions/Animations/AnimatedSprite.h"
#include "EntityType.h"

namespace Castlevania
{
	enum class Facing
	{
		Right,
		Left,
	};

	class GameObject
	{
	public:
		GameObject(EntityType type);

		EntityType GetType();
		void SetVelocity(Vector2 velocity);
		void SetLinearVelocity(float speed, float angle = 0.0f); // angle in degree
		void SetPosition(float x, float y);
		void SetPosition(Vector2 position);
		Vector2 GetPosition();

		Vector2 GetOriginPosition(); // Get the center of the object bounding box to the world
		virtual Rect GetFrameRect();
		virtual Rect GetBoundingBox();

		virtual void LoadContent(ContentManager &content);
		virtual void Update(float deltaTime);
		void UpdateDistance(float deltaTime);

		virtual void Draw(SpriteExtensions &spriteBatch);
		virtual void DrawBoundingBox(SpriteExtensions &spriteBatch); // For debugging purpose

		virtual ~GameObject();

	protected:
		EntityType type;
		Vector2 position;
		Vector2 velocity;
		float speed;

		std::unique_ptr<AnimatedSprite> sprite;
	};
}