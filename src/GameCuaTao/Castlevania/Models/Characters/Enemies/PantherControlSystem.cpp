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
		case NEAR_PLAYER:
			parent.SetActive(true);

			if (parent.GetPlayerDirection() == Direction::Left)
				parent.RunLeft();
			else // (parent.GetPlayerDirection() == Direction::Right)
				parent.RunRight();
			break;
	}
}
