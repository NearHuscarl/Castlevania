#include "StopwatchCutscene.h"
#include "Stage.h"
#include "StageEvent.h"

using namespace Castlevania;

constexpr auto STOPWATCH_TIME = 3000; // in milliseconds

StopwatchCutscene::StopwatchCutscene(Stage &stage) : Cutscene{ stage }
{
	stopwatchTimer.Start();
}

void StopwatchCutscene::Update(UpdateData &updateData)
{
	updateData.isStopwatchActive = true;

	stage.UpdateGameplay(updateData);

	if (stopwatchTimer.ElapsedMilliseconds() >= STOPWATCH_TIME)
	{
		stage.OnNotify(Subject::Empty(), CUTSCENE_ENDED);
		isComplete = true;
	}
}
