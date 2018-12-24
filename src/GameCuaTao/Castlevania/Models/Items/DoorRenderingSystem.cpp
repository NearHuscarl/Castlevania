#include "DoorRenderingSystem.h"
#include "../../Settings/Animations.h"

using namespace Castlevania;

DoorRenderingSystem::DoorRenderingSystem(Door &parent, std::string animationPath) :
	AnimationRenderingSystem{ parent, animationPath },
	parent{ parent }
{
}

void DoorRenderingSystem::OnMoveStateChanged()
{
	switch (parent.GetDoorState())
	{
		case DoorState::NORMAL:
			sprite->Play(NORMAL_ANIMATION);
			break;

		case DoorState::OPENING:
			sprite->Play(OPEN_ANIMATION);
			break;

		case DoorState::CLOSING:
			sprite->Play(CLOSE_ANIMATION);
			break;
	}
}
