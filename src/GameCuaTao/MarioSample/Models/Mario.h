#pragma once

#include "Direct2DGame/Input/Controller.h"
#include "GameObject.h"

class Mario : public GameObject, public Controller
{
public: 
	void LoadContent(ContentManager &content) override;
	void Update(unsigned long deltaTime) override;
	void Draw(ISpriteBatch_ spriteBatch) override;

private:
	void ResolveCollision();
	std::string GetAnimation();

	void Jump();

	void OnKeyState(InputManager &inputManager) override;
	void OnKeyDown(InputManager &inputManager, KeyEventArgs e) override;
	void OnKeyUp(InputManager &inputManager, KeyEventArgs e) override;
};