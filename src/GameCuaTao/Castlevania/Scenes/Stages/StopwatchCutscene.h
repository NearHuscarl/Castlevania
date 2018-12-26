#pragma once

#include "Direct2DGame/Utilities/Stopwatch.h"
#include "Cutscene.h"

namespace Castlevania
{
	class StopwatchCutscene : public Cutscene
	{
	public:
		StopwatchCutscene(Stage &stage);
		void Update(UpdateData &updateData) override;

	private:
		Stopwatch stopwatchTimer; // A stopwatch of another stopwatch >.>
	};
}