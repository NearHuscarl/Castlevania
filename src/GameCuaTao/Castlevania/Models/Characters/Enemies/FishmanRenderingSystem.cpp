#include "FishmanRenderingSystem.h"
#include "../../Settings.h"
#include "../../../Settings/Animations.h"

using namespace Castlevania;

FishmanRenderingSystem::FishmanRenderingSystem(
	Fishman &parent,
	std::string animationPath,
	std::unique_ptr<IEffect> effect)
	:
	EffectRenderingSystem{ animationPath, std::move(effect) },
	parent{ parent }
{
}

GameObject &FishmanRenderingSystem::GetParent()
{
	return parent;
}

void FishmanRenderingSystem::OnMoveStateChanged()
{
	switch (parent.GetFishmanState())
	{
		case FishmanState::LAUNCHING:
			sprite->Play(IDLE_ANIMATION);
			break;

		case FishmanState::WALKING:
			sprite->PlayCached(WALK_ANIMATION);
			break;

		case FishmanState::FALLING:
			sprite->GetCurrentAnimation().Stop();
			break;

		case FishmanState::SHOOTING:
			sprite->Play(SHOOT_ANIMATION);
			break;
	}
}
