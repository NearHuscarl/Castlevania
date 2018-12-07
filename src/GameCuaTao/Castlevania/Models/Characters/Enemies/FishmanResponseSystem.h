#pragma once

#include "../../Systems/CollisionResponse/ResponseSystem.h"
#include "Fishman.h"

namespace Castlevania
{
	class FishmanResponseSystem : public ResponseSystem
	{
	public:
		FishmanResponseSystem(Fishman &parent);
		GameObject &GetParent() override;

	protected:
		Fishman &parent;

		void OnTouchingGround(CollisionData collisionData) override;
		void OnFalling() override;
		void OnLanding() override;
	};
}