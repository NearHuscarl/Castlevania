#include "PantherRenderingSystem.h"
#include "../../Settings.h"
#include "../../../Settings/Animations.h"

using namespace Castlevania;

PantherRenderingSystem::PantherRenderingSystem(
	Panther &parent,
	std::string animationPath,
	std::unique_ptr<IEffect> effect)
	:
	EffectRenderingSystem{ animationPath, std::move(effect) },
	parent{ parent }
{
}

Sprite &PantherRenderingSystem::GetSprite()
{
	return *sprite;
}

GameObject &PantherRenderingSystem::GetParent()
{
	return parent;
}

void PantherRenderingSystem::Draw(SpriteExtensions &spriteBatch)
{
	DrawBoundingBox(spriteBatch, parent.GetActiveArea(), Color::LavenderBlue() * 0.4f); // TODO: remove debugging code

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
