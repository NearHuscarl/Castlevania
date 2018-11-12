#pragma once

#include "Controller.h"
#include "Simon.h"

namespace Castlevania
{
	class Player : public Simon
	{
	public:
		Player();
		IController *GetController();

	private:
		std::unique_ptr<Controller> controller;
	};
}