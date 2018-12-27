#include "FishmanRenderingSystem.h"
#include "../../Settings.h"
#include "../../../Settings/Animations.h"

using namespace Castlevania;

FishmanRenderingSystem::FishmanRenderingSystem(
	Fishman &parent,
	std::string animationPath,
	std::unique_ptr<IEffect> launchEffect,
	std::unique_ptr<IEffect> deadEffect,
	std::unique_ptr<IEffect> hitEffect)
	:
	EntityRenderingSystem{ parent, animationPath, std::move(deadEffect), std::move(hitEffect) },
	parent{ parent }
{
	this->launchEffect = std::move(launchEffect);
}

void FishmanRenderingSystem::Update(GameTime gameTime)
{
	EntityRenderingSystem::Update(gameTime);

	switch (parent.GetFishmanState())
	{
		case FishmanState::LAUNCHING:
			launchEffect->Update(gameTime);
			break;
	}
}

void FishmanRenderingSystem::Draw(SpriteExtensions &spriteBatch)
{
	EntityRenderingSystem::Draw(spriteBatch);

	switch (parent.GetFishmanState())
	{
		case FishmanState::LAUNCHING:
			launchEffect->Draw(spriteBatch);
			break;
	}
}

void FishmanRenderingSystem::OnMoveStateChanged()
{
	switch (parent.GetFishmanState())
	{
		case FishmanState::LAUNCHING:
			sprite->Play(IDLE_ANIMATION);
			launchEffect->Show(parent.GetOriginPosition());
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
