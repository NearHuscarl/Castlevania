#include "VampireBatRenderingSystem.h"
#include "../../Settings.h"
#include "../../../Settings/Animations.h"

using namespace Castlevania;

VampireBatRenderingSystem::VampireBatRenderingSystem(
	VampireBat &parent,
	std::string animationPath,
	std::unique_ptr<IEffect> effect)
	:
	EffectRenderingSystem{ animationPath, std::move(effect) },
	parent{ parent }
{
}

GameObject &VampireBatRenderingSystem::GetParent()
{
	return parent;
}

void VampireBatRenderingSystem::OnMoveStateChanged()
{
	if (parent.IsActive())
		sprite->Play(FLY_ANIMATION);
	else
		sprite->Play(IDLE_ANIMATION);
}
