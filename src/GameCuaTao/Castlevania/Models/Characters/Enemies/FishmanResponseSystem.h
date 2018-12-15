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
		void Update(UpdateData &updateData) override;

	protected:
		Fishman &parent;
		bool wasOnGround;
	};
}