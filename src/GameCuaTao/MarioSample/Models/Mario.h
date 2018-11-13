#pragma once

#include "GameObject.h"
#include "MarioController.h"

namespace MarioSample
{
	enum class State
	{
		WALKING_LEFT,
		WALKING_RIGHT,
		IDLE,
		JUMPING,
	};

	class Mario : public GameObject
	{
	public:
		Mario();
		State GetState();
		IController *GetController();

		void LoadContent(ContentManager &content) override;
		void Update(float deltaTime) override;
		void Draw(SpriteBatch &spriteBatch) override;

		void Jump();
		void Jumping();
		void Idle();
		void WalkLeft();
		void WalkRight();

	private:
		State state;
		MarioController controller;

		void UpdateState();
		void ResolveCollision(float deltaTime);
	};
}