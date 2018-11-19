#pragma once

#include "Direct2DGame/Content/ContentManager.h"
#include "Direct2DGame/Extensions/Collisions/Body/Body.h"
#include "Direct2DGame/Extensions/Sprites/SpriteExtensions.h"
#include "Direct2DGame/Input/IController.h"
#include "Systems/IMovementSystem.h"
#include "Systems/ICollisionSystem.h"
#include "Systems/ICollisionResponseSystem.h"
#include "IGameObject.h"
#include "EntityType.h"

namespace Castlevania
{
	struct ObjectCollection;

	class GameObject : public IGameObject
	{
	public:
		GameObject(EntityType type);

		int GetType() override;

		Vector2 GetPosition();
		void SetPosition(float x, float y);
		void SetPosition(Vector2 position);
		Vector2 GetOriginPosition(); // Get the center of the object's bounding box to the world

		void Move(Vector2 direction);
		Vector2 GetDistance() override;
		
		Vector2 GetVelocity();
		virtual void SetVelocity(Vector2 velocity);
		void SetVelocity_X(float x);
		void SetVelocity_Y(float y);
		void SetLinearVelocity(float speed, float angle = 0.0f); // angle in degree
		
		virtual RectF GetFrameRect();
		virtual RectF GetBoundingBox();

		Body &GetBody() override;

		IController *GetController();

		template<typename T>
		void Attach(std::unique_ptr<T> system);

		virtual void LoadContent(ContentManager &content);
		virtual void Update(float deltaTime, ObjectCollection *objectCollection = nullptr);
		virtual void Draw(SpriteExtensions &spriteBatch);
		virtual void DrawBoundingBox(SpriteExtensions &spriteBatch); // For debugging purpose

		virtual ~GameObject();

	protected:
		EntityType type;
		Vector2 position;
		Vector2 velocity;
		float speed;
		Body body;

	private:
		std::unique_ptr<IController> controller;
		std::unique_ptr<IMovementSystem> movementSystem;
		std::unique_ptr<ICollisionSystem> collisionSystem;
		std::unique_ptr<ICollisionResponseSystem> collisionResponseSystem;
	};
}