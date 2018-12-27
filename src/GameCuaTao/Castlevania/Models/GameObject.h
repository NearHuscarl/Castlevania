#pragma once

#include "Direct2DGame/GameTime.h"
#include "Direct2DGame/Content/ContentManager.h"
#include "Direct2DGame/Extensions/Collisions/Body/Body.h"
#include "Direct2DGame/Extensions/Sprites/SpriteExtensions.h"
#include "Systems/Control/IControlSystem.h"
#include "Systems/Movement/IMovementSystem.h"
#include "Systems/Collision/ICollisionSystem.h"
#include "Systems/CollisionResponse/ICollisionResponseSystem.h"
#include "Systems/Rendering/IRenderingSystem.h"
#include "IGameObject.h"
#include "ObjectId.h"
#include "Facing.h"
#include "../Utilities/Subject.h"
#include "../Utilities/CollisionGridData.h"

namespace Castlevania
{
	struct UpdateData;
	class CollisionGrid;

	enum class ObjectState
	{
		NORMAL,
		DYING,
		DEAD,
	};

	class GameObject : public Subject, public IGameObject
	{
	public:
		GameObject(ObjectId type);

		ObjectId GetId();
		int GetType() override;

		void SetState(ObjectState state);
		ObjectState GetState();

		Vector2 GetPosition();
		virtual void SetPosition(float x, float y);
		virtual void SetPosition(Vector2 position);

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
		void SetDirection(float angle); // angle in degree
		void SetDirection(Vector2 direction);

		float GetSpeed();
		virtual void SetSpeed(float speed);

		virtual RectF GetFrameRect();
		virtual RectF GetBoundingBox();

		Sprite *GetSprite();
		Facing GetFacing();
		virtual void SetFacing(Facing facing);
		virtual void SetVisibility(bool value);

		Body &GetBody() override;
		void Destroy();

		void EnableControl(bool value);
		void Move(Vector2 distance);
		void SwitchFacing();

		CollisionGridData GetCollisionGridData();
		void SetCollisionGridData(CollisionGridData data);

		virtual void Attach(CollisionGrid *grid);
		void Attach(std::unique_ptr<IControlSystem> system);
		void Attach(std::unique_ptr<IMovementSystem> system);
		void Attach(std::unique_ptr<ICollisionSystem> system);
		void Attach(std::unique_ptr<ICollisionResponseSystem> system);
		void Attach(std::unique_ptr<IRenderingSystem> system);

		template<typename T>
		void Detach();

		virtual void LoadContent(ContentManager &content);
		virtual void Update(UpdateData &updateData);
		virtual void Draw(SpriteExtensions &spriteBatch);

		void SendMessageToSystems(int message);
		static GameObject &NullObject();

		virtual ~GameObject();

	protected:
		ObjectId objectId;
		ObjectState state;
		Vector2 position;
		Vector2 velocity;
		float speed;
		Facing facing;
		Body body;

		CollisionGrid *collisionGrid;
		CollisionGridData collisionGridData;
		std::vector<IReceiver*> components;

		std::unique_ptr<IControlSystem> controlSystem;
		std::unique_ptr<IMovementSystem> movementSystem;
		std::unique_ptr<ICollisionSystem> collisionSystem;
		std::unique_ptr<ICollisionResponseSystem> collisionResponseSystem;
		std::unique_ptr<IRenderingSystem> renderingSystem;
	};
}