#include "PantherControlSystem.h"
#include "../../UpdateData.h"
#include "../../Settings.h"

using namespace Castlevania;

PantherControlSystem::PantherControlSystem(Panther &parent) : parent{ parent }
{
}

void PantherControlSystem::Receive(int message)
{
	switch (message)
	{
		case PLAYER_IN_RANGE:
			parent.SetActive(true);

			if (parent.GetPlayerDirection() == Direction::Left)
				parent.RunLeft();
			else // (parent.GetPlayerDirection() == Direction::Right)
				parent.RunRight();
			break;
	}
}
