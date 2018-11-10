#pragma once

#include <memory>
#include "Direct2DGame/Content/ContentManager.h"
#include "Direct2DGame/Extensions/Sprites/SpriteExtensions.h"
#include "Direct2DGame/Extensions/Animations/AnimatedSprite.h"
#include "EntityType.h"

namespace Castlevania
{
	class GameObject
	{
	public:
		GameObject(EntityType type);

		EntityType GetType();
		void SetVelocity(float velocity);
		void SetDirection(float degrees);
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

		virtual ~GameObject();

	protected:
		EntityType type;
		Transform transform;
		Vector2 direction;
		float velocity;
		float speed;

		std::unique_ptr<AnimatedSprite> sprite;
	};

	using GameObjects = std::vector<std::unique_ptr<GameObject>>;
}