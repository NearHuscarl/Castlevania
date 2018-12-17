#include "GiantBatResponseSystem.h"
#include "../../UpdateData.h"
#include "../../Settings.h"

using namespace Castlevania;

GiantBatResponseSystem::GiantBatResponseSystem(GiantBat &parent) : parent{ parent }
{
}

void GiantBatResponseSystem::Receive(int message)
{
	switch (message)
	{
		case PLAYER_IN_RANGE:
			parent.IsInRange(true);
			break;

		case PLAYER_OUT_OF_RANGE:
			parent.IsInRange(false);
			break;
	}
}

void GiantBatResponseSystem::Update(UpdateData &updateData)
{
}
