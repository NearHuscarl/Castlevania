#pragma once

#include "../../Systems/Control/ControlSystem.h"
#include "../../../Models/Factories/ObjectFactory.h"
#include "GiantBat.h"

namespace Castlevania
{
	class GiantBatControlSystem : public ControlSystem
	{
	public:
		GiantBatControlSystem(GiantBat &parent, ObjectFactory &objectFactory);
		void Update(UpdateData &updateData) override;

	private:
		GiantBat &parent;
		ObjectFactory &objectFactory;
	};
}