#pragma once

#include "Direct2DGame/Input/IController.h"
#include "Player.h"

namespace Castlevania
{
	class Controller : public IController
	{
	public:
		Controller(Player &player);

		void OnKeyStateChanged(KeyboardState &keyboardState) override;
		void OnKeyDown(int keyCode) override;
		void OnKeyUp(int keyCode) override;

	private:
		Player &player;
		KeyboardState keyboardState;
	};
}