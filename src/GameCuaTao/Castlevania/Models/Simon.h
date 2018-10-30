#pragma once

#include "GameObject.h"

namespace Castlevania
{
	enum class Direction
	{
		Left,
		Right
	};

	class Simon : public GameObject
	{
	public:
		void LoadContent(ContentManager &content) override;
		virtual void Update(float deltaTime) override;
		void Draw(SpriteBatch &spriteBatch) override;

		void Idle();
		void WalkLeft();
		void WalkRight();
		void TurnBackward();

	protected:
		enum class State
		{
			WALKING_LEFT,
			WALKING_RIGHT,
			IDLE,
			TURNING_BACKWARD,
		};

		State state;
		Direction direction;
	};
}