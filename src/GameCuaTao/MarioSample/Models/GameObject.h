#pragma once

#include <map>
#include "Direct2DGame/Base/Vector.h"
#include "Direct2DGame/Animation/Animation.h"
#include "Direct2DGame/Content/ContentManager.h"

namespace MarioSample
{
	enum Direction
	{
		Left,
		Right,
	};

	class GameObject
	{
	public:
		GameObject();

		void SetPosition(float x, float y);
		void SetSpeed(float vx, float vy);

		void SetState(int state);
		int GetState();

		virtual void LoadContent(ContentManager &content) = 0;

		virtual void Update(unsigned long deltaTime);

		// update object position: distance = velocity x deltatime
		void UpdateDistance(unsigned long deltaTime);

		virtual void Draw(ISpriteBatch_ spriteBatch);

		virtual ~GameObject();

	protected:
		Vector position;
		Vector velocity;

		Direction direction;
		int state;

		std::shared_ptr<AnimationDict> animations;
	};
}