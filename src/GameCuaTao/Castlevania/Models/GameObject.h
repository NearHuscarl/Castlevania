#pragma once

#include "Direct2DGame/Content/ContentManager.h"
#include "Direct2DGame/Extensions/Sprites/SpriteExtensions.h"
#include "Direct2DGame/Extensions/Animations/AnimatedSprite.h"
#include "Systems/CollisionSystem.h"
#include "Systems/CollisionResponseSystem.h"
#include "EntityType.h"
#include "Body/Body.h"
#include "IGameObject.h"

namespace Castlevania
{
	struct ObjectCollection;

	enum class Facing
	{
		Right,
		Left,
	};

	class GameObject : public IGameObject
	{
	public:
		GameObject();
		GameObject(RectF boundingBox);
		GameObject(EntityType type);

		EntityType GetType() override;

		Vector2 GetPosition() override;
		void SetPosition(float x, float y);
		void SetPosition(Vector2 position);
		
		Vector2 GetVelocity() override;
		void SetVelocity(Vector2 velocity);
		void SetLinearVelocity(float speed, float angle = 0.0f); // angle in degree

		Vector2 GetOriginPosition(); // Get the center of the object's bounding box to the world
		
		Body GetBody();
		virtual Rect GetFrameRect();
		virtual RectF GetBoundingBox() override;

		void SetCollisionSystem(std::unique_ptr<CollisionSystem> collisionSystem);
		void SetCollisionResponseSystem(std::unique_ptr<CollisionResponseSystem> collisionResponseSystem);

		void Move(Vector2 direction);

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
		std::unique_ptr<RectF> boundingBox;

		std::unique_ptr<CollisionSystem> collisionSystem;
		std::unique_ptr<CollisionResponseSystem> collisionResponseSystem;
	};
}