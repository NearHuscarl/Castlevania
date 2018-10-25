#pragma once

#include "GameObject.h"

namespace MarioSample
{
	class Mario : public GameObject
	{
	public:
		void LoadContent(ContentManager &content) override;
		void UpdateInput();
		void Update(float deltaTime) override;
		void Draw(SpriteBatch &spriteBatch) override;

	private:
		void ResolveCollision();

		void Jump();
		void Idle();
		void WalkLeft();
		void WalkRight();
	};
}