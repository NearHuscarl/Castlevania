#pragma once

#include "../Systems/CollisionResponse/ICollisionResponseSystem.h"
#include "WaterArea.h"

namespace Castlevania
{
	class Player;

	class WaterAreaResponseSystem : public ICollisionResponseSystem
	{
	public:
		WaterAreaResponseSystem(WaterArea &parent, EffectFactory &effectFactory);

		virtual void Receive(int message) override {};
		void Update(UpdateData &updateData) override;

	private:
		WaterArea &parent;
		EffectFactory &effectFactory;
	};
}