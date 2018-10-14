#pragma once

#include "GameObject.h"
#include "../Input/Controller.h"

class Mario : public GameObject, public Controller
{
public: 
	void LoadContent(ContentManager &content) override;
	void Update(unsigned long deltaTime) override;
	void Draw(SpritePtr spriteHandler) override;
	void SetState(int state) override;
	std::string GetAnimationState() override;

private:
	void OnKeyState(InputManager *inputManager) override;
	void OnKeyDown(InputManager *inputManager, KeyEventArgs e) override;
	void OnKeyUp(InputManager *inputManager, KeyEventArgs e) override;
};