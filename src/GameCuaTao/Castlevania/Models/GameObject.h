#pragma once

#include <memory>
#include "Direct2DGame/Content/ContentManager.h"

namespace Castlevania
{
	class GameObject
	{
	public:
		void SetPosition(Vector2 position);
		void SetPosition(float x, float y);
		void SetSpeed(float vx, float vy);

		Vector2 GetOriginPosition(); // Get the center of the object bounding box to the world
		virtual Rect GetFrameRect();
		virtual Rect GetBoundingBox();
		Animation &GetAnimation();

		virtual void LoadContent(ContentManager &content);
		virtual void Update(float deltaTime);
		void UpdateDistance(float deltaTime);

		virtual void Draw(SpriteBatch &spriteBatch);

	protected:
		Vector2 position;
		Vector2 velocity;

		std::shared_ptr<AnimationDict> animations;
		std::string currentAnimation;
	};
}