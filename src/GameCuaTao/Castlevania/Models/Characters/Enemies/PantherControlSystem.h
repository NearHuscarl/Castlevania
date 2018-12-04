#pragma once

#include "../../Systems/Control/ControlSystem.h"
#include "Panther.h"

namespace Castlevania
{
	class PantherControlSystem : public ControlSystem
	{
	public:
		PantherControlSystem(Panther &parent);
		void Receive(int message) override;

	private:
		Panther &parent;
	};
}