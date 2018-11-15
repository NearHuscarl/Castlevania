#pragma once

#include "Direct2DGame/Content/ContentManager.h"
#include "Direct2DGame/Extensions/Sprites/SpriteExtensions.h"
#include "Direct2DGame/Extensions/Animations/AnimatedSprite.h"
#include "Systems/CollisionSystem.h"
#include "EntityType.h"
#include "Body/Body.h"
#include "IDynamic.h"

namespace Castlevania
{
	struct ObjectCollection;

	enum class Facing
	{
		Right,
		Left,
	};

	class GameObject : public IDynamic
	{
	public:
		GameObject();
		GameObject(EntityType type);

		EntityType GetType() override;
		void SetVelocity(Vector2 velocity);
		Vector2 GetVelocity() override;
		void SetLinearVelocity(float speed, float angle = 0.0f); // angle in degree
		void SetPosition(float x, float y);
		void SetPosition(Vector2 position);
		Vector2 GetPosition() override;
		Body GetBody();

		Vector2 GetOriginPosition(); // Get the center of the object's bounding box to the world
		virtual Rect GetFrameRect();
		virtual Rect GetBoundingBox() override;

		virtual void LoadContent(ContentManager &content);
		virtual void Update(float deltaTime, ObjectCollection *objectCollection = nullptr);
		void UpdateDistance(float deltaTime);

		virtual void Draw(SpriteExtensions &spriteBatch);
		virtual void DrawBoundingBox(SpriteExtensions &spriteBatch); // For debugging purpose

		virtual ~GameObject();

	protected:
		EntityType type;
		Vector2 position;
		Vector2 velocity;
		float speed;
		Body body;

		std::unique_ptr<AnimatedSprite> sprite;

		CollisionSystem collisionSystem;
	};
}