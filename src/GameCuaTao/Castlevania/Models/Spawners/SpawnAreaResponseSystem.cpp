#include "SpawnAreaResponseSystem.h"
#include "../Settings.h"

using namespace Castlevania;

SpawnAreaResponseSystem::SpawnAreaResponseSystem(SpawnArea &parent) : parent{ parent }
{
}

void SpawnAreaResponseSystem::Receive(int message)
{
	switch (message)
	{
		case PLAYER_IN_RANGE:
			parent.Activate();
			break;

		case PLAYER_OUT_OF_RANGE:
			parent.Deactivate();
			break;
	}
}

void SpawnAreaResponseSystem::Update(UpdateData &updateData)
{
}
