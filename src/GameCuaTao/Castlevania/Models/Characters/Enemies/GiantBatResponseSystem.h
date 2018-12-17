#pragma once

#include "../../Systems/CollisionResponse/ResponseSystem.h"
#include "GiantBat.h"

namespace Castlevania
{
	class GiantBatResponseSystem : public ResponseSystem
	{
	public:
		GiantBatResponseSystem(GiantBat &parent);
		
		void Receive(int message) override;
		void Update(UpdateData &updateData);
	
	private:
		GiantBat &parent;
	};
}