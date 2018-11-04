#pragma once

#include <memory>
#include "Direct2DGame/Content/ContentManager.h"

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
		Animation &GetAnimation();

		virtual void LoadContent(ContentManager &content);
		virtual void Update(float deltaTime);
		void UpdateDistance(float deltaTime);

		virtual void Draw(SpriteBatch &spriteBatch);

		virtual ~GameObject();

	protected:
		Vector2 rotation;
		Vector2 position;
		float velocity;
		float speed;

		std::shared_ptr<AnimationSet> animations;
	};
}