#pragma once

#include "GameObject.h"

namespace MarioSample
{
	class Mario : public GameObject
	{
	public:
		void LoadContent(ContentManager &content) override;
		void UpdateInput() override;
		void Update(float deltaTime) override;
		void Draw(SpriteBatch &spriteBatch) override;

	private:
		void ResolveCollision();
		std::string GetAnimation();

		void Jump();
	};
}