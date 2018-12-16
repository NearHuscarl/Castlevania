#pragma once

#include "../../Systems/CollisionResponse/ICollisionResponseSystem.h"
#include "GiantBat.h"

namespace Castlevania
{
	class GiantBatResponseSystem : public ICollisionResponseSystem
	{
	public:
		GiantBatResponseSystem(GiantBat &parent);
		
		void Receive(int message) override;
		void Update(UpdateData &updateData);
	
	private:
		GiantBat &parent;
	};
}