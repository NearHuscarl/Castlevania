#pragma once

#include "Direct2DGame/Input/Controller.h"
#include "GameObject.h"

namespace MarioSample
{
	class Mario : public GameObject, public Controller
	{
	public:
		void LoadContent(ContentManager &content) override;
		void Update(float deltaTime) override;
		void Draw(SpriteBatch &spriteBatch) override;

	private:
		void ResolveCollision();
		std::string GetAnimation();

		void Jump();

		void OnKeyState(Keyboard &inputManager) override;
		void OnKeyDown(Keyboard &inputManager, KeyEventArgs e) override;
		void OnKeyUp(Keyboard &inputManager, KeyEventArgs e) override;
	};
}