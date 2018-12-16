#pragma once

#include "Direct2DGame/Content/ContentManager.h"
#include "Direct2DGame/Utilities/Stopwatch.h"
#include "Cutscene.h"
#include "../../Models/Factories/ObjectCollection.h"
#include "../../Models/Factories/ObjectFactory.h"
#include "../../Models/IBoss.h"

namespace Castlevania
{
	class BossFightCutscene : public Cutscene
	{
	public:
		BossFightCutscene(Stage &stage, ObjectCollection &objectCollection, ObjectFactory &objectFactory);

		void Update(GameTime gameTime) override;

	private:
		IBoss *boss;
		Stopwatch bossWakeupTimer;
	};
}