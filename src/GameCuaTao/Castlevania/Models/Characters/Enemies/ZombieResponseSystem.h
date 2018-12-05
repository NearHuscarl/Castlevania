#pragma once

#include "../../Systems/CollisionResponse/ResponseSystem.h"
#include "Zombie.h"

namespace Castlevania
{
	class ZombieResponseSystem : public ResponseSystem
	{
	public:
		ZombieResponseSystem(Zombie &parent);
		GameObject &GetParent() override;

	protected:
		Zombie &parent;

		void OnTouchingGround(CollisionData collisionData) override;
		void OnFalling() override;
		void OnLanding() override;
	};
}