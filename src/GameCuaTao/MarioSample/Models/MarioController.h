#pragma once

#include "Direct2DGame/Input/IController.h"

namespace MarioSample
{
	class Mario;

	class MarioController : public IController
	{
	public:
		MarioController(Mario &player);

		void OnKeyStateChanged(KeyboardState &keyboardState) override;
		void OnKeyDown(int KeyCode) override;
		void OnKeyUp(int KeyCode) override;

	private:
		Mario &player;
	};
}