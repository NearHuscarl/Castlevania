#include "PantherRenderingSystem.h"
#include "../../../Settings/Animations.h"
#include "../../../Utilities/DevTool.h"

using namespace Castlevania;

PantherRenderingSystem::PantherRenderingSystem(
	Panther &parent,
	std::string animationPath,
	std::unique_ptr<IEffect> effect)
	:
	EffectRenderingSystem{ parent, animationPath, std::move(effect) },
	parent{ parent }
{
}

void PantherRenderingSystem::Draw(SpriteExtensions &spriteBatch)
{
	if (DevTool::IsDebugging)
		DrawBoundingBox(spriteBatch, parent.GetActiveArea(), Color::LavenderBlue() * 0.4f);

	EffectRenderingSystem::Draw(spriteBatch);
}

void PantherRenderingSystem::OnMoveStateChanged()
{
	switch (parent.GetPantherState())
	{
		case PantherState::IDLE:
			sprite->Play(IDLE_ANIMATION);
			break;

		case PantherState::RUNNING:
			sprite->Play(RUN_ANIMATION);
			break;

		case PantherState::JUMPING:
			sprite->Play(JUMP_ANIMATION);
			break;
	}
}
