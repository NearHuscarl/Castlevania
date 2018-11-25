#pragma once

#include "Direct2DGame/Input/IController.h"
#include "Player.h"
#include "../../../Models/Factories/ObjectFactory.h"
#include "../../../Models/Systems/Control/IControlSystem.h"

namespace Castlevania
{
	class Controller : public IControlSystem, public IController
	{
	public:
		Controller(Player &player, ObjectFactory &objectFactory);

		void Receive(int message) {};

		void OnKeyStateChanged(KeyboardState &keyboardState) override;
		void OnKeyDown(int keyCode) override;
		void OnKeyUp(int keyCode) override;

		void Update() override;

	private:
		Player &player;
		KeyboardState keyboardState;
		ObjectFactory &objectFactory;

		void Throw();
	};
}