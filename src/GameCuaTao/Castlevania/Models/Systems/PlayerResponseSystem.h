#pragma once

#include "ICollisionResponseSystem.h"
#include "../Characters/Player/Player.h"

namespace Castlevania
{
	class PlayerResponseSystem : public ICollisionResponseSystem
	{
	public:
		PlayerResponseSystem(Player &parent);

		void Update() override;

	private:
		Player &parent;
	};
}