#pragma once

#include "Direct2DGame/Input/IController.h"
#include "Simon.h"

namespace Castlevania
{
	class Controller : public IController
	{
	public:
		Controller(Simon &player);

		void OnKeyStateChanged(KeyboardState &keyboardState) override;
		void OnKeyDown(int KeyCode) override;
		void OnKeyUp(int KeyCode) override;

	private:
		Simon &player;
		KeyboardState keyboardState;
	};
}