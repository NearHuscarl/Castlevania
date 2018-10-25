#pragma once

#include "GameObject.h"

namespace MarioSample
{
	class Mario : public GameObject
	{
	public:
		void LoadContent(ContentManager &content) override;
		void Update(float deltaTime) override;
		void Draw(SpriteBatch &spriteBatch) override;

	private:
		void UpdateState();
		void ResolveCollision();

		void Jump();
		void Jumping();
		void Idle();
		void WalkLeft();
		void WalkRight();
	};
}