#pragma once

#include "Direct2DGame/GameTime.h"
#include "Direct2DGame/Content/ContentManager.h"
#include "Direct2DGame/Extensions/Collisions/Body/Body.h"
#include "Direct2DGame/Extensions/Sprites/SpriteExtensions.h"
#include "Systems/Movement/IMovementSystem.h"
#include "Systems/Collision/ICollisionSystem.h"
#include "Systems/CollisionResponse/ICollisionResponseSystem.h"
#include "Systems/Control/IControlSystem.h"
#include "Systems/Rendering/IRenderingSystem.h"
#include "IGameObject.h"
#include "EntityType.h"
#include "Facing.h"
#include "UpdateData.h"
#include "../Utilities/Subject.h"

namespace Castlevania
{
	struct ObjectCollection;

	enum class ObjectState
	{
		NORMAL,
		DYING,
		DEAD,
	};

	class GameObject : public Subject, public IGameObject
	{
	public:
		GameObject(EntityType type);

		int GetType() override;

		void SetState(ObjectState state);
		ObjectState GetState();

		Vector2 GetPosition();
		void SetPosition(float x, float y);
		void SetPosition(Vector2 position);

		Vector2 GetDistance();
		void SetDistance(Vector2 distance);
		void SetDistance_X(float value);
		void SetDistance_Y(float value);

		Vector2 GetOriginPosition(); // Get the center of the object's rectangle
		void SetOriginPosition(Vector2 position);
		
		Vector2 GetVelocity();
		virtual void SetVelocity(Vector2 velocity);
		void SetVelocity_X(float x);
		void SetVelocity_Y(float y);
		void SetLinearVelocity(float speed, float angle = 0.0f); // angle in degree

		float GetSpeed();
		void SetSpeed(float speed);

		virtual RectF GetFrameRect();
		virtual RectF GetBoundingBox();

		Sprite *GetSprite();
		Facing GetFacing();
		virtual void SetFacing(Facing facing);
		virtual void SetVisibility(bool value);

		Body &GetBody() override;
		void Destroy();

		void EnableControl(bool value);
		void Move(Vector2 direction);
		void SwitchFacing();

		template<typename T>
		void Attach(std::unique_ptr<T> system);

		virtual void LoadContent(ContentManager &content);
		virtual void Update(GameTime gameTime, UpdateData &updateData = UpdateData::Empty());
		virtual void Draw(SpriteExtensions &spriteBatch);
		virtual void DrawBoundingBox(SpriteExtensions &spriteBatch); // For debugging purpose

		void SendMessageToSystems(int message);

		virtual ~GameObject();

	protected:
		EntityType type;
		ObjectState state;
		Vector2 position;
		Vector2 velocity;
		float speed;
		Facing facing;
		Body body;

		std::vector<IReceiver*> components;

		std::unique_ptr<IControlSystem> controlSystem;
		std::unique_ptr<IMovementSystem> movementSystem;
		std::unique_ptr<ICollisionSystem> collisionSystem;
		std::unique_ptr<ICollisionResponseSystem> collisionResponseSystem;
		std::unique_ptr<IRenderingSystem> renderingSystem;
	};
}