#include "GiantBatRenderingSystem.h"
#include "../../../Settings/Animations.h"
#include "../../../Utilities/DevTool.h"

using namespace Castlevania;

GiantBatRenderingSystem::GiantBatRenderingSystem(
	GiantBat &parent,
	std::string animationPath,
	std::unique_ptr<IEffect> deadEffect,
	std::unique_ptr<IEffect> hitEffect)
	:
	EntityRenderingSystem{ parent, animationPath, std::move(deadEffect), std::move(hitEffect) },
	parent{ parent }
{
}

void GiantBatRenderingSystem::Draw(SpriteExtensions &spriteBatch)
{
	if (DevTool::IsDebugging)
	{
		DrawBoundingBox(spriteBatch, parent.GetThreatZone(), Color::Red() * 0.3f);
		DrawBoundingBox(spriteBatch, parent.GetAttackZone(), Color::LavenderBlue() * 0.5f);
	}

	EntityRenderingSystem::Draw(spriteBatch);
}

void GiantBatRenderingSystem::OnMoveStateChanged()
{
	switch (parent.GetGiantBatState())
	{
		case GiantBatState::IDLE:
			sprite->Play(IDLE_ANIMATION);
			break;

		default:
			sprite->Play(FLY_ANIMATION);
			break;
	}
}
