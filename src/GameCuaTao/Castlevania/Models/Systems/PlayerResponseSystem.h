#pragma once

#include "CollisionResponseSystem.h"
#include "../Characters/Player/Player.h"

namespace Castlevania
{
	class PlayerResponseSystem : public CollisionResponseSystem
	{
	public:
		PlayerResponseSystem(Player &parent);

		void Update(CollisionData collisionData) override;

	private:
		Player &parent;
	};
}